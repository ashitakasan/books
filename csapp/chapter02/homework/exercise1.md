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







