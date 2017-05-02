#include <stdio.h>

int any_even_one(unsigned x){
    unsigned a = 0xAAAAAAAA;
    return !(a & x - a);
}

int main(){
    printf("%d\n", any_even_one(0xaaaaaaad));
}

