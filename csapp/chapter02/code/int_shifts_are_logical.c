#include <stdio.h>

int int_shift_are_logocal(){
    return (-1 >> 1) > 0;
}

int main(){
    printf("%d\n", int_shift_are_logocal());
}

