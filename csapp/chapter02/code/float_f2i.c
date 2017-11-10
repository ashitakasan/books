#include <stdio.h>

typedef unsigned float_bits;

int float_f2i(float_bits f){
    unsigned sign = f & 0x80000000;
    unsigned exp = (f >> 23) & 0xFF;
    unsigned frac = f & 0x7FFFFF;

    if(exp < 0x7F)                  // exp < 127，表示 0 ~ 1 的数
        return 0;

    unsigned E = exp - 127;
    unsigned remd;
    if(E <= 23)                     // E >= 23，表示 frac 需要右移
        remd = frac >> (23 - E);
    else if(E < 31)                 // 23 < E < 31，表示 frac 需要左移
        remd = frac << (E - 23);
    else                            // E > 31，则 f 大于 INT_MAX，直接返回 INT_MAX
        return 0x80000000;

    unsigned res = (1 << E) | remd;
    return (sign == 0) ? res : (~res + 1);  // 如果 f 为负，则返回其补码
}

int main(){
    unsigned i;
    int fi, si;

    for(i=0; i<0xFFFFFFFF; i++){
        fi = float_f2i(i);
        si = (int)*(float *)&i;
        if(si != fi){
            printf("%d = 0x%X, 0x%X != 0x%X, %d != %d\n", i, i, si, fi, si, fi);
            return 0;
        }
        if(i % 0x7FFFFFF == 0)
            printf("All Integer's %d/32 succeed...\n", i/0x7FFFFFF);
    }
    printf("All 32-bites Integer numbers passed!!\n");
}

