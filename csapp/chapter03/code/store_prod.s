	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 12
	.globl	_store_prod
	.p2align	4, 0x90
_store_prod:                            ## @store_prod
## BB#0:
    pushl   %ebp
    movl    %esp, %ebp
    pushl   %esi
    pushl   %ebx

    movl	12(%ebp), %esi
    movl	20(%ebp), %eax
    movl	%eax, %edx
    sarl	$31, %edx
    movl	%edx, %ecx
    imull	%esi, %ecx
    movl	16(%ebp), %ebx
    imull	%eax, %ebx
    addl	%ebx, %ecx
    mull	%esi
    leal	(%ecx, %edx), %edx
    movl	8(%ebp), %ecx
    movl	%eax, (%ecx)
    movl	%edx, 4(%ecx)

    popl    %ebx
    popl    %esi
    popl    %ebp
    retl

	.globl	_main
	.p2align	4, 0x90
_main:                                  ## @main
## BB#0:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	subl	$64, %esp
	calll	L1$pb
L1$pb:
	popl	%eax
	leal	L_.str-L1$pb(%eax), %ecx
	movl	$0, -12(%ebp)
	movl	$1025, -16(%ebp)        ## imm = 0x401
	movl	$4, -20(%ebp)
	movl	-16(%ebp), %edx
	movl	-12(%ebp), %esi
	movl	%esp, %edi
	movl	%esi, 8(%edi)
	movl	%edx, 4(%edi)
	leal	-32(%ebp), %edx
	movl	%edx, (%edi)
	movl	$4, 12(%edi)
	movl	%eax, -36(%ebp)         ## 4-byte Spill
	movl	%ecx, -40(%ebp)         ## 4-byte Spill
	calll	_store_prod
	movl	-32(%ebp), %eax
	movl	-28(%ebp), %ecx
	movl	%esp, %edx
	movl	%ecx, 8(%edx)
	movl	%eax, 4(%edx)
	movl	-36(%ebp), %eax         ## 4-byte Reload
	leal	L_.str-L1$pb(%eax), %ecx
	movl	%ecx, (%edx)
	calll	_printf
	xorl	%ecx, %ecx
	movl	%eax, -44(%ebp)         ## 4-byte Spill
	movl	%ecx, %eax
	addl	$64, %esp
	popl	%esi
	popl	%edi
	popl	%ebp
	retl

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"dest = %lld\n"


.subsections_via_symbols
