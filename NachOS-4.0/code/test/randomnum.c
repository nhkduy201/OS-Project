#include "syscall.h"

int main()
{
  int rn;
  rn = RandomNum();

  Halt();
  /* not reached */
}
