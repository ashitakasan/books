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
- A. `(%esi) = x, (%ebx) = n, (%edi) = result, (%edx) = mask`
- B. `result = 1431655765; mask = -2147483648 = INT_MIN = 10...0b`
- C. `mask != 0`
- D. `mask = ((unsigned)mask) >> (n & 0xFF)`
- E. `result ^= mask & x`

## 3.57
```
int cread_alt(int *xp){
	int p = (int)NULL;
	return *(xp ? xp : &p);
}
```

## 3.58



