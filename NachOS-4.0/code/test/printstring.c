/* printstring.c
  syscall that print a integer.
*/

#include "syscall.h"

int main()
{

  PrintString("Hello",6);

  Halt();
  /* not reached */
}
