/* readnum.c
  syscall that read a char.
*/

#include "syscall.h"

int main()
{
  int c = ReadNum();

  Halt();
  /* not reached */
}
