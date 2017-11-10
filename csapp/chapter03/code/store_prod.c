#include <stdio.h>

typedef long long ll_t;

void store_prod(ll_t *dest, ll_t x, int y){
    *dest = x * y;
}

int main(){
    ll_t x = 34134134134301l;
    int y = 4;
    ll_t dest;
    store_prod(&dest, x, y);
    printf("%lld * %d = %lld\n", x, y, dest);
}

