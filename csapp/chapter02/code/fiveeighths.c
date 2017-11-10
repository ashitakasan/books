#include <stdio.h>
#include <limits.h>

// 低比特位先乘再除，高比特位先除再乘；再根据低比特位计算结果来舍入
int fiveeighths(int x){
    int low = x & 0x7;
    int high = x & ~0x7;
    int low_res = (low + (low << 2)) >> 3;
    int high_res = (high >> 3) + (high >> 1);           // 1/8 + 1/2 = 5/8
    int round = (low & 7) && (x & (1<<31));
    return high_res + low_res + round;
}

int main(){
    int a = 0xFFFFFFF1;
    printf("%d: %d\n", a, fiveeighths(a));
}

