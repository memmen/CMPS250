// File f.s
     .text
		  .p2align 4,,15
    .globl f
	  .type	f, @function
f:
	pushl	%ebp                                                       
	  movl	%esp, %ebp
	    subl	$16, %esp
	  movl	$0, -4(%ebp)
loop:	  cmpl $0            , 8(%ebp)     //Top of loop
    jle	done
	  movl	8(%ebp),             %eax
	                 addl	%eax, -4(%ebp)
	  subl	$1, 8(%ebp)
            jmp   loop              //Bottom of loop
    done:	  movl	-4(%ebp), %eax
//---------------------------------------------------
  leave
          ret

		  