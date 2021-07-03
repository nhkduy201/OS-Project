/* readstring.c
  syscall that read a string.
*/

#include "syscall.h"

int main()
{
  int len = 10;
  char str[10];
  ReadString(str, len);

  Halt();
  /* not reached */
}
