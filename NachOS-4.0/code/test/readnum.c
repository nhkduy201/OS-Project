/* readsnum.c
  syscall that read a num.
*/

#include "syscall.h"

int main()
{
  int n;
  n = ReadNum();

  Halt();
  /* not reached */
}
