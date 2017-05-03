#include <stdio.h>
#include <string.h>

void copy_int(int val, void *buf, int maxbytes){
    if(maxbytes >= (int)sizeof(val))
        memcpy(buf, (void *)&val, sizeof(val));
}

int main(){
    char buf[4];
    copy_int(1000, buf, 10);
    printf("%d\n", *(int *)buf);
}

