/* printstring.c
  syscall that print a integer.
*/

#include "syscall.h"

int main()
{

  PrintString("Hello");

  Halt();
  /* not reached */
}
