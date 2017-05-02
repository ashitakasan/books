#include <stdio.h>

unsigned replace_byte(unsigned x, unsigned char b, int i){
    if(i >= sizeof(int))
        return x;
    return (~(0xFF << (i * 8)) & x) | (b << (i * 8));
}

int main(){
    printf("0x%X\n", replace_byte(0x12345678, 0xAB, 2));
    printf("0x%X\n", replace_byte(0x12345678, 0xAB, 1));
    printf("0x%X\n", replace_byte(0x12345678, 0xAB, 0));
    printf("0x%X\n", replace_byte(0x12345678, 0xAB, 4));
}

