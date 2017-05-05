#include <stdio.h>
#include <limits.h>

int signed_high_prod(int x, int y){
    long z = x * (long)y;
    return z >> 32;
}

unsigned unsigned_high_prod(unsigned x, unsigned y){
    int mid = (x >> 31) * y + (y >> 31) * x;
    return signed_high_prod(x, y) + mid;
}

int main(){
    int x = 0xF2345678;
    int y = x;
    printf("signed: 0x%lX %% 0x%X = 0x%lX = 0x%X\n", (long)x*y, x*y, (long)x*y >> 32, signed_high_prod(x, y));
    printf("unsigned: 0x%X\n", unsigned_high_prod(x, y));
}

