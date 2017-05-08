#include <stdio.h>

typedef unsigned float_bits;

float_bits float_i2f(int i){
    if(i == 0)
        return i;

    unsigned sign = i & 0x80000000;
    unsigned u = sign == 0 ? (unsigned)i : (~i + 1);

    unsigned E = 0;
    unsigned tmp = u;
    while(tmp > 1){
        tmp >>= 1;
        E += 1;
    }

    unsigned exp = E + 127;
    unsigned frac = (u - (1<<E)) << (E > 23 ? 0 : 23-E);
    // 所有 E > 23 的奇整数都不能准确表示，即大于 0x1000000 的奇数
    if(E > 23){
        unsigned base = 1 << (E-23);            // base 即精度，两个相邻 float int 的差
        unsigned base_bits = frac & (base - 1);
        // 如果 frac 精度以下数超过精度的一半，或精度位及精度下一位都为1，则进位
        if(base_bits > (base>>1) || ((frac & base) && (frac & (base>>1)))){
            if((frac | (base-1)) == ((1<<E) - 1)){      // 如果 frac 低 E 位全为 1，则进位到 exp，并清零 frac
                exp += 1;
                frac = 0;
            }
            else{
                frac += (base >> 1);            // frac 进位，即加上精度的一半
            }
        }
        frac >>= E-23;
    }

    return sign | (exp << 23) | frac;
}

int main(){
    unsigned i, uf;
    float sf;

    for(i=0; i<0xFFFFFFFF; i++){
        uf = float_i2f(i);
        sf = (float)(int)i;
        if(sf != *(float *)&uf){
            printf("%d = 0x%X, 0x%X != 0x%X, %f != %f\n", i, i, *(int *)&sf, uf, sf, *(float *)&uf);
            return 0;
        }
        if(i % 0x7FFFFFF == 0)
            printf("All Integer's %d/32 succeed...\n", i/0x7FFFFFF);
    }
    printf("All 32-bites Integer numbers passed!!\n");
}

