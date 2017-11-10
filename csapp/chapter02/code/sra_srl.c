#include <stdio.h>

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

int main(){
    printf("sra: %d\n", sra(-128, 3));
    printf("srl: %d\n", srl(128, 4));
}

