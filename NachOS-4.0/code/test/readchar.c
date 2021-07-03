/* readchar.c
  syscall that read a char.
*/

#include "syscall.h"
//#include "stdio.h" //No file in directory

int main()
{
  /* char r;
  r = (char)ReadChar();
  printf(r); */

  ReadChar();

  Halt();
  /* not reached */
}
