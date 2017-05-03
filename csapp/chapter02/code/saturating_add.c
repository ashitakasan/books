#include <stdio.h>
#include <limits.h>

int saturating_add(int x, int y){
    int s = x + y;
    int x0 = x >> 31;           // 取出 x、y、s 首位比特，确定其正负
    int y0 = y >> 31;           // 正+正=负：正溢出，负+负=正：负溢出
    int s0 = s >> 31;           // result = s + a * (INT_MAX - s) + b * (INT_MIN - s)

    int a = !x0 && !y0 && !!s0;
    int b = !!x0 && !!y0 && !s0;
    return s + (~(a-1) & (INT_MAX - s)) + (~(b-1) & (INT_MIN - s));
}

int main(){
    int a = (1 << 31);
    int b = -2;
    printf("%d + %d = %d\n", a, b, saturating_add(a, b));
}
