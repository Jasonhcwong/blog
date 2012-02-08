	.file	"strlen.c"
	.text
	.p2align 4,,15
.globl naiveStrlen
	.type	naiveStrlen, @function
naiveStrlen:
.LFB681:
	.cfi_startproc
	xorl	%eax, %eax
	cmpb	$0, (%rdi)
	movq	%rdi, %rdx
	je	.L3
	.p2align 4,,10
	.p2align 3
.L6:
	addq	$1, %rdx
	cmpb	$0, (%rdx)
	jne	.L6
	movq	%rdx, %rax
	subq	%rdi, %rax
.L3:
	rep
	ret
	.cfi_endproc
.LFE681:
	.size	naiveStrlen, .-naiveStrlen
	.p2align 4,,15
.globl betterStrlen
	.type	betterStrlen, @function
betterStrlen:
.LFB682:
	.cfi_startproc
	testb	$7, %dil
	movq	%rdi, %rdx
	je	.L11
	xorl	%eax, %eax
	cmpb	$0, (%rdi)
	jne	.L26
	jmp	.L13
	.p2align 4,,10
	.p2align 3
.L15:
	cmpb	$0, (%rdx)
	.p2align 4,,5
	je	.L28
.L26:
	addq	$1, %rdx
	testb	$7, %dl
	.p2align 4,,5
	jne	.L15
.L11:
	movq	%rdx, %rax
	movabsq	$-72340172838076673, %rsi
	jmp	.L16
	.p2align 4,,10
	.p2align 3
.L18:
	cmpb	$1, 1(%rax)
	je	.L29
	cmpb	$2, 2(%rax)
	.p2align 4,,3
	je	.L30
	cmpb	$3, 3(%rax)
	.p2align 4,,5
	je	.L31
	cmpb	$4, 4(%rax)
	.p2align 4,,5
	je	.L32
	cmpb	$5, 5(%rax)
	.p2align 4,,5
	je	.L33
	cmpb	$6, 6(%rax)
	.p2align 4,,5
	je	.L34
	cmpb	$7, 7(%rax)
	.p2align 4,,5
	je	.L35
.L17:
	addq	$8, %rax
.L16:
	movq	(%rax), %rcx
	leaq	(%rcx,%rsi), %rdx
	notq	%rcx
	andq	%rcx, %rdx
	andl	$1, %edx
	je	.L17
	cmpb	$0, (%rax)
	jne	.L18
	subq	%rdi, %rax
	ret
.L35:
	subq	%rdi, %rax
	addq	$7, %rax
.L13:
	rep
	ret
	.p2align 4,,10
	.p2align 3
.L28:
	movq	%rdx, %rax
	subq	%rdi, %rax
	ret
.L29:
	subq	%rdi, %rax
	addq	$1, %rax
	ret
.L30:
	subq	%rdi, %rax
	addq	$2, %rax
	ret
.L31:
	subq	%rdi, %rax
	addq	$3, %rax
	.p2align 4,,1
	ret
.L32:
	subq	%rdi, %rax
	addq	$4, %rax
	.p2align 4,,1
	ret
.L33:
	subq	%rdi, %rax
	addq	$5, %rax
	.p2align 4,,1
	ret
.L34:
	subq	%rdi, %rax
	addq	$6, %rax
	.p2align 4,,1
	ret
	.cfi_endproc
.LFE682:
	.size	betterStrlen, .-betterStrlen
	.p2align 4,,15
.globl main
	.type	main, @function
main:
.LFB685:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	movl	$19999, %edi
	pushq	%r12
	.cfi_def_cfa_offset 24
	pushq	%rbp
	.cfi_def_cfa_offset 32
	movabsq	$-6640827866535438581, %rbp
	.cfi_offset 6, -32
	.cfi_offset 12, -24
	.cfi_offset 13, -16
	pushq	%rbx
	.cfi_def_cfa_offset 40
	subq	$8, %rsp
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -40
	call	srandom
	movl	$100, %edi
	call	malloc
	leaq	99(%rax), %r12
	movq	%rax, %r13
	movq	%rax, %rbx
	.p2align 4,,10
	.p2align 3
.L37:
	call	random
	movq	%rax, %rcx
	imulq	%rbp
	movq	%rcx, %rax
	sarq	$63, %rax
	addq	%rcx, %rdx
	sarq	$6, %rdx
	subq	%rax, %rdx
	leaq	(%rdx,%rdx,4), %rax
	leaq	(%rax,%rax,4), %rax
	salq	$2, %rax
	subq	%rax, %rcx
	addl	$1, %ecx
	movb	%cl, (%rbx)
	addq	$1, %rbx
	cmpq	%r12, %rbx
	jne	.L37
	movb	$0, 99(%r13)
	addq	$8, %rsp
	xorl	%eax, %eax
	popq	%rbx
	popq	%rbp
	popq	%r12
	popq	%r13
	ret
	.cfi_endproc
.LFE685:
	.size	main, .-main
	.p2align 4,,15
.globl testFunc
	.type	testFunc, @function
testFunc:
.LFB684:
	.cfi_startproc
	movq	%rbx, -40(%rsp)
	movq	%rbp, -32(%rsp)
	movq	%rsi, %rbx
	.cfi_offset 6, -40
	.cfi_offset 3, -48
	movq	%r12, -24(%rsp)
	movq	%r13, -16(%rsp)
	movl	%ecx, %r12d
	.cfi_offset 13, -24
	.cfi_offset 12, -32
	movq	%r14, -8(%rsp)
	xorl	%esi, %esi
	subq	$40, %rsp
	.cfi_def_cfa_offset 48
	movq	%rdx, %rbp
	movq	%r8, %r13
	.cfi_offset 14, -16
	call	gettimeofday
	testl	%r12d, %r12d
	jle	.L41
	xorl	%r14d, %r14d
	.p2align 4,,10
	.p2align 3
.L42:
	addl	$1, %r14d
	movq	%rbp, %rdi
	call	*%r13
	cmpl	%r14d, %r12d
	jg	.L42
.L41:
	movq	%rbx, %rdi
	movq	8(%rsp), %rbp
	movq	(%rsp), %rbx
	movq	16(%rsp), %r12
	movq	24(%rsp), %r13
	xorl	%esi, %esi
	movq	32(%rsp), %r14
	addq	$40, %rsp
	jmp	gettimeofday
	.cfi_endproc
.LFE684:
	.size	testFunc, .-testFunc
	.p2align 4,,15
.globl sse42Strlen
	.type	sse42Strlen, @function
sse42Strlen:
.LFB683:
	.cfi_startproc
	pxor	%xmm1, %xmm1
	movq	%rdi, %rax
	.p2align 4,,10
	.p2align 3
.L46:
	movdqu	(%rax), %xmm0
	pcmpistri	$8, %xmm0, %xmm1
	addq	$16, %rax
	cmpl	$16, %ecx
	je	.L46
	movslq	%ecx,%rcx
	subq	%rdi, %rcx
	leaq	-16(%rax,%rcx), %rax
	ret
	.cfi_endproc
.LFE683:
	.size	sse42Strlen, .-sse42Strlen
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
