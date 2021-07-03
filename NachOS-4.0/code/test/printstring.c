/* printstring.c
  syscall that print a integer.
*/

#include "syscall.h"

int main()
{

  PrintString("Hello World");

  Halt();
  /* not reached */
}
