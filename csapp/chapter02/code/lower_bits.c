#include <stdio.h>

int lower_bits(int x, int n){
    int mask = (1 << (n - 1) << 1) - 1;
    return x | mask;
}

int main(){
    printf("0x%X\n", lower_bits(0, 17));
}

