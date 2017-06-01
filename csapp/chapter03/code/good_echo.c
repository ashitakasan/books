#include <stdio.h>

#define BUFFERSIZE 8

void good_echo(){
    char buf[BUFFERSIZE];
    while(fgets(buf, BUFFERSIZE, stdin)){
        int i;
        for(i=0; i<BUFFERSIZE; i++){
            if(buf[i] == 0x31)
                return;
        }
        printf("%s", buf);
    }
}

void good_echo0(){
    char *start = (char *)malloc(BUFFERSIZE);
    char *buf = start;
    int size = BUFFERSIZE;
xun:
    while(fgets(buf, BUFFERSIZE, stdin)){
        int i;
        for(i=0; i<BUFFERSIZE; i++){
            if(buf[i] == 0x31)
                goto end;
            else if(buf[i] == 0x0A){
                printf("%s", start);
                free(start);
                start = (char *)malloc(BUFFERSIZE);
                buf = start;
                size = BUFFERSIZE;
                goto xun;
            }
        }
        buf += BUFFERSIZE - 1;
        size += BUFFERSIZE - 1;
        start = realloc(start, size);
    }
end:
    printf("%s\n", start);
}

int main(){
    printf("Please Enter Something:\n");
    good_echo0();
}

