## 3.54
```c
int decode2(int x, int y, int z){
	int t = y - z;
	int s = t << 15;
	s >>= 15;
	return s * (x ^ t);
}
```

## 3.55
```nasm
movl	12(%ebp), %esi		; get x low 32bits
movl	20(%ebp), %eax		; get y
movl	%eax, %edx			; mov y to %edx
sarl	$31, %edx 			; get sign of y
movl	%edx, %ecx			; save sign to %ecx
imull	%esi, %ecx			; (y sign) * (x low 32bits) to %ecx
movl	16(%ebp), %ebx		; get x high 32bits
imull	%eax, %ebx			; (x high 32bits) * y to %ebx
addl	%ebx, %ecx			; add high 32bits result with low 32bits carry
mull	%esi					; (x low 32bits) * y, low in %eax, high in %edx
leal	(%ecx, %edx), %edx	; add result's high 32bits together
movl	8(%ebp), %ecx			; get dest
movl	%eax, (%ecx)			; save result low 32bits to dest
movl	%edx, 4(%ecx)			; save result high 32bits to dest
```

## 3.56
```c
int loop(int x, int n){
	int result = 1431655765;
	int mask;
	for(mask = -2147483648; mask != 0; mask = ((unsigned)mask) >> (n & 0xFF)){
		result ^= mask & x;
	}
	return result;
}
```
- A. `%esi = x, %ebx = n, %edi = result, %edx = mask`
- B. `result = 1431655765; mask = -2147483648 = INT_MIN = 10...0b`
- C. `mask != 0`
- D. `mask = ((unsigned)mask) >> (n & 0xFF)`
- E. `result ^= mask & x`

## 3.57
```c
int cread_alt(int *xp){
	int p = (int)NULL;
	return *(xp ? xp : &p);
}
```

## 3.58
```c
typedef enum {MODE_A, MODE_B, MODE_C, MODE_D, MODE_E} mode_t;

int switch3(int *p1, int *p2, mode_t action){
	int result = 0;
	switch(action){
		case MODE_A:
			result = *p1;
			*p1 = *p2;
			break;
		case MODE_B:
			result = *p1 + *p2;
			*p2 = result;
			break;
		case MODE_C:
			*p2 = 15;
			result = *p1;
			break;
		case MODE_D:
			*p2 = *p1;
		case MODE_E:
			result = 17;
		default:
			if(result == 0)
				return -1;
	}
	return result;
}
```

## 3.59
```c
int switch_prob(int x, int n){
	int result = x;
	switch(n){
		case 40:
		case 42:
			result = x << 3;
			break;
		case 43:
			result = x >> 3;
			break;
		case 44:
			x *= 7;
		case 45:
			x *= x;
		default:
			result = x + 17;
	}
	return result;
}
```

## 3.60
```c
int A[R][S][T];
int store_ele(int i, int j, int k, int *dest){
	*dest = A[i][j][k];
	return sizeof(A);
}
```
- A. `&D[i][j][k] = xD + L(S * T * i + T * j + k)`
- B.

```nasm
movl	8(%ebp), %ecx				; get i
movl	12(%ebp), %eax			; get j
leal	(%eax,%eax,8), %eax		; i * 9
movl	%ecx, %edx				; mov i to %edx
sall	$6, %edx					; i * 64
subl	%ecx, %edx				; i * 63
addl	%edx, %eax				; i * 63 + j * 9
addl	16(%ebp), %eax			; i * 63 + j * 9 + k
movl	A(,%eax,4), %edx			; get A[63*i + 9 * j + k]
movl	20(%ebp), %eax			; get dest
movl	%edx, (%eax)				; set *dest = A[63*i + 9 * j + k]
movl	$2772, %eax				; set result
```
因此：

```c
R * S * T = 2772;
S * T = 63;
T = 9;
S = 7;
R = 44;
```

## 3.61
```c
int var_prod_ele(int n, int A[n][n], int B[n][n], int i, int k){
	int j;
	int result = 0;
	for(j = 0; j < n; j++)
		result += A[i][j] * (*B)[j * n + k];
	return result;
}
```

## 3.62
- A. `M = 76 / 4 = 19`
- B. `%edi = i, %ecx = j`
- C.

```c
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
```

## 3.63
```c
#define	E1(n)		(3 * (n))			// line4, line18 --> %esi = E1(n)
#define	E2(n)		(2 * (n) - 1)		// line8, line17 --> %ebx = E2(n)
```

## 3.64
```nasm
word_sum:
pushl	%ebp						; save stack addr
movl	%esp, %ebp				; create stack frame
pushl	%ebx						; save %ebx
movl	8(%ebp), %eax				; get result save addr
movl	16(%ebp), %ebx			; %ebx = s1.v
movl	12(%ebp), %edx			; %edx = s1.p
movl	(%edx), %edx				; %edx = *s1.p
leal	(%edx,%ebx), %ecx		; %ecx = %edx + %ebx = *s1.p + s1.v
movl	%ecx, 4(%eax)				; save s2.sum to (%eax+4)
imull	%ebx, %edx				; %edx = *s1.p * s1.v
movl	%edx, (%eax)				; save s2.prod to (%eax)
popl	%ebx						; restore %ebx
popl	%ebp						; restore %ebp
ret		$4							; return and release result's addr
```
```nasm
diff:
pushl	%ebp						; save stack addr
movl	%esp, %ebp				; create stack frame
subl	$20, %esp					; allocate 20 bytes on stack
leal	-8(%ebp), %edx			; allocate 8 bytes for word_sum's return value
leal	8(%ebp), %eax				; %eax = x's addr
movl	%eax, 4(%esp)				; s1.p = &x
movl	12(%ebp), %eax			; %eax = y
movl	%eax, 8(%esp)				; s1.v = y
movl	%edx, (%esp)				; the first param, word_sum's result's addr
call	word_sum					; call word_sum
subl	$4, %esp					; 
movl	-8(%ebp), %eax			; %eax = s2.prod
subl	-4(%ebp), %eax			; %eax = s2.prod - s2.sum
leave								; movl %ebp, %esp; popl %ebp
ret									; return
```
- A. 
	- `8(%ebp)`: word_sum's return value's addr
	- `12(%ebp)`: s1.p
	- `16(%ebp)`: s1.v
- B. 
	- `-4(%ebp)`: word_sum's return value s2.sum
	- `-8(%ebp)`: word_sum's return value s2.prod
	- `-12(%ebp)`: s1.v as param
	- `-16(%ebp)`: s1.p as param
	- `-20(%ebp)`: word_sum's return value's addr
- C. 
	- Allocate sizeof(struct) to store return value if returns a struct
	- Save every field of a struct on stack
	- Transport the address of the return value's storage on stack
- D. 
	- Get the return value's storage address from stack
	- Create a struct, filled field
	- Save every field of the struct to the storage address

## 3.65
```nasm
movl	12(%ebp), %eax			; get q
movl	28(%eax), %edx			; get v2 = q->u
addl	8(%eax), %edx				; get v1 = q->t
movl	8(%ebp), %eax				; get p
movl	%edx, 44(%eax)			; set p->y = v1 + v2
```
> ` &str2.t - &str2 = 8;`					--> __5 <= B <= 8__  
> `sizeof(struct str2) = 28 + 4 = 32;`	--> __13 <= 2B <= 16__  
> so: __B = 7 or 8__  
> `&str1.y - &str1 = 44; 2 * A * B = 44;` --> __20 < A * B <= 22__  
> so: __A = 3, B = 7__

## 3.66








