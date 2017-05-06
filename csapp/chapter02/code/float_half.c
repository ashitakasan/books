#include <stdio.h>
#include <math.h>

typedef unsigned float_bits;

float_bits float_half(float_bits f){
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;
    if(exp == 0xFF)                                 // ∞/2 = ∞
        return f;

    if(exp == 0){
        frac = (frac >> 1) + ((frac & 3) == 3);     // 最低位为 11 时需要向上舍入
    }
    else if(exp == 1){                              // exp 为 1 时需要移到小数位
        exp = 0;
        frac = (frac >> 1) + ((frac & 3) == 3) + (1 << 22);
    }
    else{
        exp -= 1;
    }

    return (sign << 31) | (exp << 23) | frac;
}

int main(){
    unsigned i = 0;
    for(i=0; i<=0xFFFFFFFF; i++){
        float f = *(float *)&i;
        float_bits absf = float_half(i);
        float hf = f/2;
        if(f/2 != *(float *)&absf)
            printf("0x%X: 0x%X != 0x%X\n", i, *(int *)&hf, *(int *)&absf);
    }
}

