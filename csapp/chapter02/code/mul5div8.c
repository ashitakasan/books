#include <stdio.h>

int divide_power2(int x, int k){
    int sign = !!(x >> 31);
    int round = sign && (x & ~(~0 << k));
    return (x >> k) + round;
}

int mul5div8(int x){
    int mid = x + (x << 2);
    return divide_power2(mid, 3);
}

int main(){
    printf("%d\n", mul5div8(0xFFFFFFF0));
}

