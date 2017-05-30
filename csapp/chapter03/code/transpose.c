#include <stdio.h>

#define M 3

void transpose0(int A[M][M]){
	int i, j;
	for(i = 0; i < M; i++){
		for(j = 0; j < i; j++){
			int t = A[i][j];
			A[i][j] = A[j][i];
			A[j][i] = t;
		}
	}
}

void transpose(int A[M][M]){
	int i, j;
	for(i = 0; i < M; i++){
        int *Ai = *(A + i);
        int *Aj = (*A) + i;
		for(j = 0; j < i; j++){
			int t = *Aj;
			*Aj = Ai[j];
			Ai[j] = t;
            Aj += M;
		}
	}
}

int main(){
    int A[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    transpose(A);
    for(int i=0; i<M; i++){
        for(int j=0; j<M; j++)
            printf("%d ", A[i][j]);
        printf("\n");
    }
}

