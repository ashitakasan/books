	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 12
	.globl	_sum
	.p2align	4, 0x90
_sum:                                   ## @sum
## BB#0:
	pushl	%ebp
	movl	%esp, %ebp
	calll	L0$pb
L0$pb:
	popl	%ecx
	movl	12(%ebp), %eax
	addl	8(%ebp), %eax
	addl	%eax, _accum-L0$pb(%ecx)
	popl	%ebp
	retl

	.globl	_accum                  ## @accum
.zerofill __DATA,__common,_accum,4,2

.subsections_via_symbols
