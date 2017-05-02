#include <stdio.h>

int is_little_endian(){
    int i = 1;
    int head = (int)*(char *)&i;
    if(head == 1)
        return 1;
    else
        return 0;
}

int main(){
    printf("%d\n", is_little_endian());
}

