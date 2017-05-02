#include <stdio.h>

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

int main(){
    printf("0x%X\n", leftmost_one(0xF0000000));
}

