#include <stdio.h>

int tsub_ovf(int x, int y){
    int z = -y;
    int s = x + z;
    if(x > 0 && z > 0 && s < 0)
        return 1;
    else if(x < 0 && z < 0 && s >= 0)
        return 1;
    else
        return 0;
}

int main(){
    int x = -1, y = (1 << 31);
    printf("%d\n", tsub_ovf(x, y));
    printf("%d - %d = %d\n", x, y, x - y);
}
