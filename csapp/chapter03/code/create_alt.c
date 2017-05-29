#include <stdio.h>

int cread_alt(int *xp){
    int p = (int)NULL;
    return *(xp ? xp : &p);
}

int main(){
    int p = 14;
    printf("cread_alt = %d\n", cread_alt(NULL));
}

