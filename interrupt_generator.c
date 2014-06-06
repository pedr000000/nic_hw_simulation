#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/*
int main(int argn, char **argv)
{

	 __asm__ ("movl %eax, %ebx\n\t"
	       "movl $56, %esi\n\t"
	       "movl %ecx, $label(%edx,%ebx,$4)\n\t"
	       "movb %ah, (%ebx)");
	//__asm__("int $5\n");
	return 0;
}
*/
int main (void) {
      int operand1, operand2, sum, accumulator;
       
      operand1 = rand (); operand2 = rand ();
      printf("%d %d\n", operand1, operand2); 
      __asm__ ("movl %1, %0\n\t"
      	       "addl %2, %0"
	       : "=r" (sum)			/* output operands */
	       : "r" (operand1), "r" (operand2) /* input operands */
	       : "0");				/* clobbered operands */
      
      accumulator = sum;
      
      __asm__ ("addl %1, %0\n\t"
	       "addl %2, %0"
	       : "=r" (accumulator)
	       : "0" (accumulator), "g" (operand1), "r" (operand2)
	       : "0");
	//__asm__("int $5");
	__asm__("int $0x80");

      return accumulator;
    }
