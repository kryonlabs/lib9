	.file	"getcallerpc-Linux-amd64.S"
	.type	getcallerpc,@function
	.global	getcallerpc
getcallerpc:
	movq	(%rbp), %rax
	ret
