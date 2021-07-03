/* printchar.c
  syscall that print char.
*/

#include "syscall.h"

int main()
{

  PrintChar('a');

  Halt();
  /* not reached */
}
