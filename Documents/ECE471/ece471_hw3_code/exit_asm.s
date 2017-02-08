
@ Syscall defines
.equ SYSCALL_EXIT,     1


        .globl _start
_start:

        @================================
        @ Exit
        @================================
exit:
	mov	r0,#4                 @Puts 4 into r0
	mov	r7,#SYSCALL_EXIT      @moves SYSCALL_EXIT into system call register
	swi	0X0                   @activates system call

