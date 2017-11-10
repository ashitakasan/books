#include <stdio.h>

int divide_power2(int x, int k){
    int sign = !!(x >> 31);
    int round = sign && (x & ~(~0 << k));
    return (x >> k) + round;
}

int main(){
    printf("%d, %d\n", 0xFFFFFFF7, divide_power2(0xFFFFFFF7, 1));
}

