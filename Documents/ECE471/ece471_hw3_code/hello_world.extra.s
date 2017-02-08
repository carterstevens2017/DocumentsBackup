.arm

@ Syscall Definitions
.equ SYSCALL_EXIT,     1
.equ SYSCALL_WRITE,    4

@ Other Definitions
.equ STDOUT,	       1

        .globl _start
_start:

	mov	r9,#0
loop:	mov	r10,#16
	cmp	r9,r10
	beq	done

	mov	r0,r9
	mov	r11,#15
	sub	r0,r11,r0
	bl	print_number
	add	r9,r9,#1
	ldr	r1,=message
	bl	print_string
	b	loop
done:




        @================================
        @ Exit
        @================================
exit:
	mov	r0,#0			@ Return a zero
        mov	r7,#SYSCALL_EXIT	@
        swi	0x0			@ Run the system call


	@====================
	@ print_string
	@====================
	@ Null-terminated string to print pointed to by r1
	@ the value in r1 is destroyed by this routine


@.thumb

print_string:

	push    {r0,r2,r7,r10,lr}	// Save r0,r2,r7,r10,lr on stack

	mov	r2,#0			//sets r2=0
	mov	r4,#0			//sets offset to 0
comp:	ldr	r3,[r1,r4]		//loads address of first char in string
	
	cmp	r3,#0			//compares current char to null
	beq	end			//if current char==null, end
	
	add	r2,r2,#1		//increments counter by 1
	add	r4,r4,#1		//increments offset by one byte
	b	comp	
end:
	

	@ The length of the string pointed to by r1
	@ Should be put in r2 by your code above

	mov	r0,#STDOUT		// R0 Print to stdout
					// R1 points to our string
					// R2 is the length
	mov	r7,#SYSCALL_WRITE	// Load syscall number
	swi	0x0			// System call

	pop	{r0,r2,r7,r10,pc}       // pop r0,r2,r3,pc from stack

.arm

        @#############################
	@ print_number
	@#############################
	@ r0 = value to print
	@ r0 is destroyed by this routine

print_number:
	push	{r10,LR}	// Stores the LR address in r10
        ldr	r10,=buffer	//
        add	r10,r10,#10	//

divide:
	mov	r1,#10		//

	bl	divide_by_10	//
	add	r8,r8,#0x30	//
	strb	r8,[r10],#-1	//
	adds	r0,r7,#0	//
	bne	divide		//

write_out:
        add	r1,r10,#1	//

        bl	print_string	//

        pop	{r10,LR}	//

        mov	pc,lr		//

	##############################
	# divide_by_10
	##############################
	# r0=numerator
        # r4,r5 trashed
	# r7 = quotient, r8 = remainder

divide_by_10:
	ldr	r4,=429496730		// 1/10 * 2^32
	sub	r5,r0,r0,lsr #30
	umull	r8,r7,r4,r5		// {r8,r7}=r4*r5

	mov	r4,#10			// calculate remainder
	mul	r8,r7,r4
	sub	r8,r0,r8

	mov	pc,lr

.data
message:	.string ": ECE471 is cool\n"

@ BSS
.lcomm buffer,11
