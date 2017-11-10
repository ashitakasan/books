	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 12
	.globl	_word_sum
	.p2align	4, 0x90
_word_sum:                              ## @word_sum
## BB#0:
word_sum:
pushl   %ebp
movl    %esp, %ebp
pushl   %ebx
movl    8(%ebp), %eax
movl    16(%ebp), %ebx
movl    12(%ebp), %edx
movl    (%edx), %edx
leal    (%edx,%ebx), %ecx
movl    %ecx, 4(%eax)
imull   %ebx, %edx
movl    %edx, (%eax)
popl    %ebx
popl    %ebp
ret     $4

	.globl	_diff
	.p2align	4, 0x90
_diff:                                  ## @diff
## BB#0:
pushl   %ebp
movl    %esp, %ebp
subl    $20, %esp
leal    -8(%ebp), %edx
leal    8(%ebp), %eax
movl    %eax, 4(%esp)
movl    12(%ebp), %eax
movl    %eax, 8(%esp)
movl    %edx, (%esp)
call    word_sum
subl    $4, %esp
movl    -8(%ebp), %eax
subl    -4(%ebp), %eax
leave
ret
	.globl	_main
	.p2align	4, 0x90
_main:                                  ## @main
## BB#0:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%eax
	calll	L2$pb
L2$pb:
	popl	%esi
	subl	$8, %esp
	pushl	$4
	pushl	$3
	calll	_diff
	addl	$8, %esp
	leal	L_.str-L2$pb(%esi), %ecx
	pushl	%eax
	pushl	%ecx
	calll	_printf
	addl	$16, %esp
	xorl	%eax, %eax
	addl	$4, %esp
	popl	%esi
	popl	%ebp
	retl

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"diff() = %d\n"


.subsections_via_symbols
