## 2.55
```c
#include <stdio.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, int len) {
    int i;
    for(i = 0; i < len; i++)
        printf(" %.2x", start[i]);
    printf("\n");
}

int main(){
    int i = 12345;
    show_bytes((byte_pointer)&i, sizeof(int));
    float f = 12345.0;
    show_bytes((byte_pointer)&f, sizeof(f));
    return 0;
}
```
运行结果：

```c
gcc -o show-bytes.out show-bytes.c && ./show-bytes.out
39 30 00 00
00 e4 40 46
```
运行程序的机器是 小端法。

## 2.57
```c
void show_short(short s){
    show_bytes((byte_pointer)&s, sizeof(short));
}

void show_long(long l){
    show_bytes((byte_pointer)&l, sizeof(long));
}

void show_double(double l){
    show_bytes((byte_pointer)&l, sizeof(double));
}
```

## 2.58
```c
int is_little_endian(){
    int i = 1;
    int head = (int)*(char *)&i;
    if(head == 1)
        return 1;
    else
        return 0;
}
```

## 2.59
```c
int combine(int x, int y){
    return (x & 0xFF) | (y & ~0xFF);
}
```

## 2.60
```c
unsigned replace_byte(unsigned x, unsigned char b, int i){
    if(i >= sizeof(int))
        return x;
    return (~(0xFF << (i * 8)) & x) | (b << (i * 8));
}
```

## 2.61
A. `!!x`  
B. `!!~x`  
C. `!!(x & (1 << ((sizeof(int)-1) << 3))`  
D. `!!(~x & 0xFF)`

## 2.62
```c
int int_shift_are_logocal(){
    return (-1 >> 1) > 0;
}
```

## 2.63
```c
int sra(int x, int k){
    int xsrl = (unsigned) x >> k;
    int shift = (sizeof(int) << 3) - k;
    return xsrl | (((1 << k) - 1) << shift);
}

int srl(int x, int k){
    unsigned xsra = (int)x >> k;
    int shift = (sizeof(int) << 3) - k;
    return xsra & ((1 << shift) - 1);
}
```

## 2.64
```c
int any_even_one(unsigned x){
    unsigned a = 0xAAAAAAAA;
    return !(a & x - a);
}
```

## 2.65
```c
// 每次计算当前位的前 2^n 位的奇偶性，n = 0,1,2,3,4
int even_ones(unsigned x){
    x ^= x >> 1;
    x ^= x >> 2;
    x ^= x >> 4;
    x ^= x >> 8;
    x ^= x >> 16;
    return !(x & 1);
}

// 分治思想，每次计算 2^n 个位 1 的个数，n = 0,1,2,3,4
int even_ones0(unsigned x){
    x = (x & 0x55555555) + (x >> 1) & 0x55555555;
    x = (x & 0x33333333) + (x >> 2) & 0x33333333;
    x = (x & 0x0F0F0F0F) + (x >> 4) & 0x0F0F0F0F;
    x = (x & 0x00FF00FF) + (x >> 8) & 0x00FF00FF;
    x = (x & 0x0000FFFF) + (x >> 16) & 0x0000FFFF;
    return ! (x & 1);
}
```

## 2.66
```c
// 将 x 变为 00...01...11 形式，并保留最高位
int leftmost_one(unsigned x){
    int head = x & 0x80000000;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return head | ((x + 1) >> 1);
}
```

## 2.67
A. 一些编译器在处理大于字长 w 的移位时，会将移位数 `s mod w` 的结果作为移位数  
B.

```c
int int_size_is_32(){
    int set_msb = 1 << 31;
    int beyond_msb = (1 << 30) << 2;
    return set_msb && !beyond_msb;
}
```
C.

```c
int int_size_is_320(){
    int set_msb = 1 << 15 << 15 << 1;
    int beyond_msb = 1 << 15 << 15 << 2;
    return set_msb && !beyond_msb;
}
```

## 2.68
```c
int lower_bits(int x, int n){
    int mask = (1 << (n - 1) << 1) - 1;
    return x | mask;
}
```

## 2.69
```c
int rotate_right(unsigned x, int n){
    int mask = (1 << n) - 1;
    int head = x & mask;
    return (head << (sizeof(int)*8 - n)) | (x >> n);
}
```

## 2.70
```c
int fits_bits(int x, int n){
    int mask = 1 << (n-1);
    return !!(x & mask);
}
```

## 2.71
A. 不能表示负数  
B.

```c
int xbyte(packed_t word, int bytenum){
    return (word >> (bytenum << 3)) - ((word >> 31) << 8);
}
```

## 2.72
A. maxbytes 为 int 类型，计算 maxbytes - sizeof(int) 时，会转换为 unsigned int 再计算，如果 maxbytes < sizeof(int)，则计算结果为很大的整数，使得 if 判断总是成功：

```c
1 - sizeof(int) = 4294967293
```
B.

```c
void copy_int(int val, void *buf, int maxbytes){
    if(maxbytes >= (int)sizeof(val))
        memcpy(buf, (void *)&val, sizeof(val));
}
```

## 2.73
```c
int saturating_add(int x, int y){
    int s = x + y;
    int x0 = x >> 31;           // 取出 x、y、s 首位比特，确定其正负
    int y0 = y >> 31;           // 正+正=负：正溢出，负+负=正：负溢出
    int s0 = s >> 31;           // result = s + a * (INT_MAX - s) + b * (INT_MIN - s)

    int a = !x0 && !y0 && !!s0;
    int b = !!x0 && !!y0 && !s0;
    return s + (~(a-1) & (INT_MAX - s)) + (~(b-1) & (INT_MIN - s));
}
```

## 2.74
```c
int tsub_ovf(int x, int y){
    int z = -y;
    int s = x + z;
    if(x > 0 && z > 0 && s < 0)
        return 1;
    else if(x < 0 && z < 0 && s >= 0)
        return 1;
    else
        return 0;
}
```

## 2.75
```c
unsigned unsigned_high_prod(unsigned x, unsigned y){
    int mid = (x >> 31) * y + (y >> 31) * x;
    return signed_high_prod(x, y) + mid;
}
```

## 2.76
A. x + (x << 2)  
B. x + (x << 3)  
C. (x << 5) - (x << 1)  
D. (x << 3) - (x << 6)

## 2.77
```c
int divide_power2(int x, int k){
    int sign = !!(x >> 31);
    int round = sign && (x & ~(~0 << k));
    return (x >> k) + round;
}
```

## 2.78
```c
int divide_power2(int x, int k){
    int sign = !!(x >> 31);
    int round = sign && (x & ~(~0 << k));
    return (x >> k) + round;
}

int mul5div8(int x){
    int mid = x + (x << 2);
    return divide_power2(mid, 3);
}
```

## 2.79
```c
// 低比特位先乘再除，高比特位先除再乘；再根据低比特位计算结果来舍入
int fiveeighths(int x){
    int low = x & 0x7;
    int high = x & ~0x7;
    int low_res = (low + (low << 2)) >> 3;
    int high_res = (high >> 3) + (high >> 1);           // 1/8 + 1/2 = 5/8
    int round = (low & 7) && (x & (1<<31));
    return high_res + low_res + round;
}
```

## 2.80
A. `~0 << n`  
B. `(~0 << m) & ~(~0 << (m+n))`

## 2.81
A. False `x = 0, y = INT_MIN` —— `-x < -y: 0 < -INT_MIN`  
B. True  `((x+y)<<5)+x-y = 32*(x+y)+x-y = 33*x+31*y`  
C. False `x = 1, y = -1` —— `~x+~y: 11...10, ~(x+y): 11..11`  
D. True 算法运算的比特级别是不分符号位的  
E. True 无论正数负数，末位的比特位都是正系数

## 2.82
A. Y = y/(2^k-1)  
a. `1/7`  
b. `9/15 = 3/5`  
c. `7/63`

## 2.83
```c
int float_ge(float x, float y){
    unsigned ux = *(unsigned *)&x;
    unsigned uy = *(unsigned *)&y;

    unsigned sx = ux >> 31;
    unsigned sy = uy >> 31;

    return (sx+sy == 0) ? (ux >= uy) : (ux <= uy);
}
```

## 2.84
__V = (-1)^s * M * 2^E__  
`Bias=2^(k-1)-1`  
A.  
`e=2^(k-1)+1, E=2, f=1/4, M=5/4, V=5.0, bits=0 10...01 0100...0`  
B.  
`if 2^(k-1)-1 >= n: `  
`e=n+2^(k-1)-1, E=n, f=1-2^(-n), M=2-2^(-n), V=(2-2^(-n))*2^n, bits=0 e 11...1  `  
`if 2^(k-1)-1 < n: `  
`e=2^k-2, E=2^(k-1)-1, f=1-2^(1-2^(k-1)), M=2-2^(1-2^(k-1)), V=(2-2^(1-2^(k-1)))*2^(2^(k-1)-1), bits=0 11...10 11...10...0`  
C.  
`e=2^k-3, E=2^(k-1)-2, f=0, M=1, V=2^(2^(k-1)-2), bits=0 11...101 00...0`

32位的  
A: 0x40A00000 (5.0)  
B: 0x4B7FFFFF (16777215.000000)  
C: 0x7E800000 (85070591730234615865843651857942052864.000000)

## 2.85
	  描述		| 	二进制		|		值		| 十进制
-------------	| -----------	|------------	|----------
最小正非规格化数| 00...01		| 2^(-63)\*2^(2-2^14)| 3.645199531882474602528405934E-4951
最小正规格化数	| 00..0110..0	| 2^(2-2^14)	| 3.362103143112093506262677817E-4932
最大规格化数	| 01..1011..1	| (2-2^(-63))*(2^(2^14-1)) | 1.189731495357231765021263853E+4932

## 2.86
   描述		| Hex	| 	  M		| 	E	| 	  V
---------	| ----	| -------	| ----	| -------
    -0		| 8000	|	  0		|	0	|	-0.0
  最小>1	| 3F01	| 1+(2^-8)|	0	| 1+(2^-8)
 	256		| 4700	|	  0		|	8	|	256.0
最大非规格化| 7EFF	| 2-2^(-8)|  63	| (2-2^(-8)) * 2^63
   - ∞		| FF00	|	  0		|	∞	|	 - ∞
  0x3AA0	| 3AA0	|	13/8	|  -5	|	13/256

## 2.87
格式A位		|	格式A值		|	格式B位		|	格式B值
---------	| ----------	| -----------	| ---------
101110001	|	 -9/16		| 101100010	|	 -9/16
010110101	|	 208.0		| 011101010	|	 208.0
100111110	|	-7/1024	| 100001110	|	-7/1014
000000101	|	 5/2^17	| 000000001	|	 1/1024
111011000	|	 -2^12		| 111101111	|	 -248.0
011000100	|	 768.0		| 011110000	|	   +∞

## 2.88
A. False `x=INT_MAX: (double)x=2147483647, (double)(float)x=2147483648`  
B. False `x=y=INT_MAX: dx+dx=INT_MAX*2, (double)(x+y)=-2`  
C. True 由 int 转换而来的 double 相加不会溢出或者丢失精度  
D. True 对于 int 转来的整浮点数的乘法，交换后结果是不变的，即使计算结果不准确  
E. False `x=1,y=0: dx/dx=1, dy/dy=NaN`

## 2.89
```c
float fpwr2(int x){
    unsigned exp, frac;
    unsigned u;

    if(x < -149){       	// -23 + (1 - 127)  太小
        exp = 0;
        frac = 0;
    }
    else if(x < -126){  	// 1 - 127         非规格化
        exp = 0;
        frac = 1 << (x+149);
    }
    else if(x < 128){   	// 255 - 127        规格化
        exp = x + 127;
        frac = 0;
    }
    else {              	// 255              太大
        exp = 0xFF;
        frac = 0;
    }
    u = exp << 23 | frac;
    return *(float *)&u;
}
```

## 2.90
A.  
`0x40490FDB = 0b0 10000000 10010010000111111011011`  
`Bias=127, e=128, E=1, V=(f+1)*2^E = 1.5707963705062866*2 = 3.1415927410125732`  
B. `22/7=3+1/7: y=001, k=3, 7/22 = 11.001001001...`  
C. `223/7=3+10/71: y=10*483939977, k=35, 10/71=11.00100100000011100110110000101011010...`
从二进制小数点后第 9 位开始不同

## 2.91
```c
float_bits float_absval(float_bits f){
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;
    if(exp == 0xFF && frac != 0)
        return f;
    return f & 0x7FFFFFFF;
}
```

## 2.92
```c
float_bits float_negate(float_bits f){
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;
    if(exp == 0xFF && frac != 0)
        return f;
    return (!sign << 31) | (exp << 23) | frac;
}
```

## 2.93
```c
float_bits float_half(float_bits f){
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;
    if(exp == 0xFF)                                 // ∞/2 = ∞
        return f;

    if(exp == 0){
        frac = (frac >> 1) + ((frac & 3) == 3);     // 最低位为 11 时需要向上舍入
    }
    else if(exp == 1){                              // exp 为 1 时需要移到小数位
        exp = 0;
        frac = (frac >> 1) + ((frac & 3) == 3) + (1 << 22);
    }
    else{
        exp -= 1;
    }

    return (sign << 31) | (exp << 23) | frac;
}

```

## 2.94
```c
float_bits float_twice(float_bits f){
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;
    if(exp == 0xFF)                     // ∞*2 = ∞
        return f;

    if(exp == 0){                       // 小数位进位到整数位
        exp = frac >> 22;
        frac = frac << 1;
    }
    else if(exp == 0xFE){               // 超出最大值，赋值 ∞
        exp = 0xFF;
        frac = 0;
    }
    else{
        exp += 1;
    }

    return (sign << 31) | (exp << 23) | frac;
}
```

## 2.95

















