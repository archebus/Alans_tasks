	.file	"task1.c"
	.text
	.globl	branchlessFunction
	.type	branchlessFunction, @function
branchlessFunction:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	%edx, -12(%rbp)
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	sete	%al
	movzbl	%al, %edx
	movl	-8(%rbp), %eax
	cmpl	-12(%rbp), %eax
	sete	%al
	movzbl	%al, %eax
	imull	%edx, %eax
	movl	-4(%rbp), %ecx
	movl	-8(%rbp), %edx
	addl	%edx, %ecx
	movl	-12(%rbp), %edx
	addl	%ecx, %edx
	imull	%edx, %eax
	movl	%eax, %ecx
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	sete	%al
	movzbl	%al, %edx
	movl	-8(%rbp), %eax
	cmpl	-12(%rbp), %eax
	setne	%al
	movzbl	%al, %eax
	imull	%edx, %eax
	imull	-12(%rbp), %eax
	addl	%eax, %ecx
	movl	-8(%rbp), %eax
	cmpl	-12(%rbp), %eax
	sete	%al
	movzbl	%al, %edx
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	setne	%al
	movzbl	%al, %eax
	imull	%edx, %eax
	imull	-4(%rbp), %eax
	addl	%eax, %ecx
	movl	-4(%rbp), %eax
	cmpl	-12(%rbp), %eax
	sete	%al
	movzbl	%al, %edx
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	setne	%al
	movzbl	%al, %eax
	imull	%edx, %eax
	imull	-8(%rbp), %eax
	addl	%eax, %ecx
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	setne	%al
	movzbl	%al, %edx
	movl	-8(%rbp), %eax
	cmpl	-12(%rbp), %eax
	setne	%al
	movzbl	%al, %eax
	imull	%eax, %edx
	movl	-4(%rbp), %eax
	cmpl	-12(%rbp), %eax
	setne	%al
	movzbl	%al, %eax
	imull	%eax, %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%ecx, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	branchlessFunction, .-branchlessFunction
	.globl	compareFunction
	.type	compareFunction, @function
compareFunction:
.LFB1:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	movl	%esi, -24(%rbp)
	movl	%edx, -28(%rbp)
	movl	-20(%rbp), %eax
	cmpl	-24(%rbp), %eax
	jne	.L4
	movl	-24(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jne	.L4
	movl	$1, %edx
	jmp	.L5
.L4:
	movl	$0, %edx
.L5:
	movl	-20(%rbp), %ecx
	movl	-24(%rbp), %eax
	addl	%eax, %ecx
	movl	-28(%rbp), %eax
	addl	%ecx, %eax
	imull	%edx, %eax
	movl	%eax, -12(%rbp)
	movl	-20(%rbp), %eax
	cmpl	-24(%rbp), %eax
	jne	.L6
	movl	-20(%rbp), %eax
	cmpl	-28(%rbp), %eax
	je	.L6
	movl	$1, %eax
	jmp	.L7
.L6:
	movl	$0, %eax
.L7:
	imull	-28(%rbp), %eax
	movl	%eax, %edx
	movl	-24(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jne	.L8
	movl	-24(%rbp), %eax
	cmpl	-20(%rbp), %eax
	je	.L8
	movl	$1, %eax
	jmp	.L9
.L8:
	movl	$0, %eax
.L9:
	imull	-20(%rbp), %eax
	addl	%eax, %edx
	movl	-20(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jne	.L10
	movl	-20(%rbp), %eax
	cmpl	-24(%rbp), %eax
	je	.L10
	movl	$1, %eax
	jmp	.L11
.L10:
	movl	$0, %eax
.L11:
	imull	-24(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -8(%rbp)
	movl	-20(%rbp), %eax
	cmpl	-24(%rbp), %eax
	je	.L12
	movl	-24(%rbp), %eax
	cmpl	-28(%rbp), %eax
	je	.L12
	movl	-20(%rbp), %eax
	cmpl	-28(%rbp), %eax
	je	.L12
	movl	$1, %edx
	jmp	.L13
.L12:
	movl	$0, %edx
.L13:
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	movl	%eax, -4(%rbp)
	movl	-12(%rbp), %edx
	movl	-8(%rbp), %eax
	addl	%eax, %edx
	movl	-4(%rbp), %eax
	addl	%edx, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	compareFunction, .-compareFunction
	.globl	tradFunction
	.type	tradFunction, @function
tradFunction:
.LFB2:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	%edx, -12(%rbp)
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jne	.L16
	movl	-8(%rbp), %eax
	cmpl	-12(%rbp), %eax
	jne	.L16
	movl	-4(%rbp), %edx
	movl	-8(%rbp), %eax
	addl	%eax, %edx
	movl	-12(%rbp), %eax
	addl	%edx, %eax
	jmp	.L17
.L16:
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jne	.L18
	movl	-12(%rbp), %eax
	jmp	.L17
.L18:
	movl	-8(%rbp), %eax
	cmpl	-12(%rbp), %eax
	jne	.L19
	movl	-4(%rbp), %eax
	jmp	.L17
.L19:
	movl	-4(%rbp), %eax
	cmpl	-12(%rbp), %eax
	jne	.L20
	movl	-8(%rbp), %eax
	jmp	.L17
.L20:
	movl	$5, %eax
.L17:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	tradFunction, .-tradFunction
	.section	.rodata
.LC0:
	.string	"Testing correctness:"
	.align 8
.LC1:
	.string	"Case (%d,%d,%d): Traditional=%d, Comparator=%d, Branchless=%d"
.LC2:
	.string	"ERROR: Results don't match!"
.LC3:
	.string	"  -> PASSED!"
	.text
	.globl	main
	.type	main, @function
main:
.LFB3:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$112, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$5, -80(%rbp)
	movl	$5, -76(%rbp)
	movl	$5, -72(%rbp)
	movl	$2, -68(%rbp)
	movl	$2, -64(%rbp)
	movl	$7, -60(%rbp)
	movl	$3, -56(%rbp)
	movl	$8, -52(%rbp)
	movl	$8, -48(%rbp)
	movl	$9, -44(%rbp)
	movl	$4, -40(%rbp)
	movl	$9, -36(%rbp)
	movl	$1, -32(%rbp)
	movl	$2, -28(%rbp)
	movl	$3, -24(%rbp)
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, -108(%rbp)
	jmp	.L22
.L26:
	movl	-108(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rbp, %rax
	subq	$80, %rax
	movl	(%rax), %eax
	movl	%eax, -104(%rbp)
	movl	-108(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rbp, %rax
	subq	$76, %rax
	movl	(%rax), %eax
	movl	%eax, -100(%rbp)
	movl	-108(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rbp, %rax
	subq	$72, %rax
	movl	(%rax), %eax
	movl	%eax, -96(%rbp)
	movl	-96(%rbp), %edx
	movl	-100(%rbp), %ecx
	movl	-104(%rbp), %eax
	movl	%ecx, %esi
	movl	%eax, %edi
	call	tradFunction
	movl	%eax, -92(%rbp)
	movl	-96(%rbp), %edx
	movl	-100(%rbp), %ecx
	movl	-104(%rbp), %eax
	movl	%ecx, %esi
	movl	%eax, %edi
	call	compareFunction
	movl	%eax, -88(%rbp)
	movl	-96(%rbp), %edx
	movl	-100(%rbp), %ecx
	movl	-104(%rbp), %eax
	movl	%ecx, %esi
	movl	%eax, %edi
	call	branchlessFunction
	movl	%eax, -84(%rbp)
	movl	-88(%rbp), %r8d
	movl	-92(%rbp), %edi
	movl	-96(%rbp), %ecx
	movl	-100(%rbp), %edx
	movl	-104(%rbp), %eax
	subq	$8, %rsp
	movl	-84(%rbp), %esi
	pushq	%rsi
	movl	%r8d, %r9d
	movl	%edi, %r8d
	movl	%eax, %esi
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	addq	$16, %rsp
	movl	-92(%rbp), %eax
	cmpl	-88(%rbp), %eax
	jne	.L23
	movl	-92(%rbp), %eax
	cmpl	-84(%rbp), %eax
	je	.L24
.L23:
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L25
.L24:
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L25:
	addl	$1, -108(%rbp)
.L22:
	cmpl	$4, -108(%rbp)
	jle	.L26
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L28
	call	__stack_chk_fail@PLT
.L28:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
