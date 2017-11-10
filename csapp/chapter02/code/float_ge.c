#include <stdio.h>
#include <limits.h>
#include <float.h>

int float_ge(float x, float y){
    unsigned ux = *(unsigned *)&x;
    unsigned uy = *(unsigned *)&y;

    unsigned sx = ux >> 31;
    unsigned sy = uy >> 31;

    return (sx+sy == 0) ? (ux >= uy) : (ux <= uy);
}

int main(){
    float x = -1.5, y = 1.49;
    printf("%f >= %f ? %d\n", x, y, float_ge(x, y));

    int i = 0x3F800000;
    printf("%f - %f\n", *(float *)&i, (float)INT_MAX);
}

