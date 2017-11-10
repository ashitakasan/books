#include <stdio.h>

float fpwr2(int x){
    unsigned exp, frac;
    unsigned u;

    if(x < -149){       // -23 + (1 - 127)  太小
        exp = 0;
        frac = 0;
    }
    else if(x < -126){  // 1 - 127         非规格化
        exp = 0;
        frac = 1 << (x+149);
    }
    else if(x < 128){   // 255 - 127        规格化
        exp = x + 127;
        frac = 0;
    }
    else {              // 255              太大
        exp = 0xFF;
        frac = 0;
    }
    u = exp << 23 | frac;
    return *(float *)&u;
}

int main(){
    int x = -149;
    float f = fpwr2(x);
    printf("2^%d = 0x%.8X, %.150f\n", x, *(int *)&f, f);
}

