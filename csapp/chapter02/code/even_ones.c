#include <stdio.h>

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

int main(){
    printf("%d\n", even_ones(0b1100));
}

