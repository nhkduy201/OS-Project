/* readchar.c
  syscall that read a char.
*/

#include "syscall.h"

int main()
{
  char c = ReadChar();

  Halt();
  /* not reached */
}
