#include <stdio.h>

typedef unsigned packed_t;

int xbyte(packed_t word, int bytenum){
    return (word >> (bytenum << 3)) - ((word >> 31) << 8);
}

int main(){
    int res = xbyte(0xF2345678, 3);
    printf("0x%X = %d\n", res, res);
}

