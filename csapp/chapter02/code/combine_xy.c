#include <stdio.h>

int combine(int x, int y){
    return (x & 0xFF) | (y & ~0xFF);
}

int main(){
    printf("0x%x\n", combine(0x89ABCDEF, 0x76543210));
    return 0;
}

