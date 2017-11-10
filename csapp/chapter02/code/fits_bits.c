#include <stdio.h>

int fits_bits(int x, int n){
    int mask = 1 << (n-1);
    return !!(x & mask);
}

int main(){
    printf("%d\n", fits_bits(0xF0, 3));
}

