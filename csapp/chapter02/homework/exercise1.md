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





