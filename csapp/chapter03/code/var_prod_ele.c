#include <stdio.h>
#include <limits.h>

int var_prod_ele(int n, int A[n][n], int B[n][n], int i, int k){
	int j;
	int result = 0;
	for(j = 0; j < n; j++)
		result += A[i][j] * (*B)[j * n + k];
	return result;
}

int var_prod_ele0(int n, int A[n][n], int B[n][n], int i, int k){
	int j;
	int result = 0;
	for(j = 0; j < n; j++)
		result += A[i][j] * B[j][k];
	return result;
}

int main(){
    int A[5][5] = {
        {1, 2, 3, 4, 5432423},
        {1, 2, 3, 4, 5567567},
        {113214, 231243, 331431123, 4312321, 52134324},
        {1, 2, 3, 4, 5678567},
        {1, 2, 3, 4, 5563542}
    };
    int sum;
    for(unsigned i=0; i<235435345; i++){
        sum += var_prod_ele(5, A, A, 2, 4);
        A[2][4]++;
    }
    printf("var_prod_ele() = %d\n", sum);
}

