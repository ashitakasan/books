#include <stdio.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, int len) {
    int i;
    for(i = 0; i < len; i++)
        printf(" %.2x", start[i]);
    printf("\n");
}

void show_int(int i){
    show_bytes((byte_pointer)&i, sizeof(int));
}

void show_float(float f){
    show_bytes((byte_pointer)&f, sizeof(float));
}

void show_short(short s){
    show_bytes((byte_pointer)&s, sizeof(short));
}

void show_long(long l){
    show_bytes((byte_pointer)&l, sizeof(long));
}

void show_double(double d){
    show_bytes((byte_pointer)&d, sizeof(double));
}

void show_pointer(void *p){
    show_bytes((byte_pointer)&p, sizeof(void *));
}

int main(){
    short s = 127;
    show_short(s);
    int i = 12345;
    show_int(i);
    long l = 123213123l;
    show_long(l);

    float f = 12345.0;
    show_float(f);
    double d = 12321124314131.346435435;
    show_double(d);

    float *p = &f;
    show_pointer(&p);
    return 0;
}

