#include <stdio.h>
#include <math.h>

typedef unsigned float_bits;

float_bits float_absval(float_bits f){
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;
    if(exp == 0xFF && frac != 0)
        return f;
    return f & 0x7FFFFFFF;
}

int main(){
    unsigned i = 0;
    for(i=0; i<=0xFFFFFFFF; i++){
        float f = *(float *)&i;
        float_bits absf = float_absval(i);
        if(fabs(f) != *(float *)&absf)
            printf("0x%X: %f != %.50f\n", i, fabs(f), *(float *)&absf);
    }
}

