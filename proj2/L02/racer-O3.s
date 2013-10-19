	.file	"racer.c"
	.text
	.p2align 4,,15
	.globl	racer
	.type	racer, @function
racer:
.LFB3:
	.cfi_startproc
	subl	$28, %esp
	.cfi_def_cfa_offset 32
	movl	$mutex, (%esp)
	call	pthread_mutex_lock
	movl	$20000000, %eax
	.p2align 4,,7
	.p2align 3
.L2:
	movl	ring, %edx
	addl	$1, %edx
	subl	$1, %eax
	movl	%edx, ring
	jne	.L2
	movl	$mutex, 32(%esp)
	addl	$28, %esp
	.cfi_def_cfa_offset 4
	jmp	pthread_mutex_unlock
	.cfi_endproc
.LFE3:
	.size	racer, .-racer
	.comm	mutex,24,4
	.globl	ring
	.bss
	.align 4
	.type	ring, @object
	.size	ring, 4
ring:
	.zero	4
	.ident	"GCC: (SUSE Linux) 4.7.2 20130108 [gcc-4_7-branch revision 195012]"
	.section	.comment.SUSE.OPTs,"MS",@progbits,1
	.string	"Ospwg"
	.section	.note.GNU-stack,"",@progbits
