#include <stdio.h>
#include <math.h>

typedef unsigned float_bits;

float_bits float_twice(float_bits f){
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;
    if(exp == 0xFF)                     // ∞*2 = ∞
        return f;

    if(exp == 0){                       // 小数位进位到整数位
        exp = frac >> 22;
        frac = frac << 1;
    }
    else if(exp == 0xFE){               // 超出最大值，赋值 ∞
        exp = 0xFF;
        frac = 0;
    }
    else{
        exp += 1;
    }

    return (sign << 31) | (exp << 23) | frac;
}

int main(){
    unsigned i = 0;
    for(i=0; i<=0xFFFFFFFF; i++){
        float f = *(float *)&i;
        float_bits absf = float_twice(i);
        float hf = f*2;
        if(f*2 != *(float *)&absf)
            printf("0x%X: 0x%X != 0x%X\n", i, *(int *)&hf, *(int *)&absf);
    }
}

