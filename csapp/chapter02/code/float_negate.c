#include <stdio.h>
#include <math.h>

typedef unsigned float_bits;

float_bits float_negate(float_bits f){
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;
    if(exp == 0xFF && frac != 0)
        return f;
    return (!sign << 31) | (exp << 23) | frac;
}

int main(){
    unsigned x = 0x7F800000;
    printf("0x%X\n", float_negate(x));
    unsigned i = 0;
    for(i=0; i<=0xFFFFFFFF; i++){
        float f = *(float *)&i;
        float_bits absf = float_negate(i);
        if(-f != *(float *)&absf)
            printf("0x%X: %f != %.50f\n", i, -f, *(float *)&absf);
    }
}

