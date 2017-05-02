#include <stdio.h>

int rotate_right(unsigned x, int n){
    int mask = (1 << n) - 1;
    int head = x & mask;
    return (head << (sizeof(int)*8 - n)) | (x >> n);
}

int main(){
    printf("0x%X\n", rotate_right(0x12345678, 0));
}

