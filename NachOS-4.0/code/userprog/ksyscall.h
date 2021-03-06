/**************************************************************
 *
 * userprog/ksyscall.h
 *
 * Kernel interface for systemcalls 
 *
 * by Marcus Voelp  (c) Universitaet Karlsruhe
 *
 **************************************************************/

#ifndef __USERPROG_KSYSCALL_H__
#define __USERPROG_KSYSCALL_H__

#include "kernel.h"
#include "math.h"

void SysHalt()
{
  kernel->interrupt->Halt();
}

int SysAdd(int op1, int op2)
{
  return op1 + op2;
}

void SysPrintNum(int number)
{
  int powOfTen;

  if (number == 0)
  {
    kernel->synchConsoleOut->PutChar('0');
    return;
  }

  if (number < 0)
  {
    kernel->synchConsoleOut->PutChar('-');
    number = -number;
  }

  for (int i = log10(number); i > -1; --i)
  {
    powOfTen = (int)pow(10, i);
    kernel->synchConsoleOut->PutChar(char(48 + number / powOfTen));
    number %= powOfTen;
  }
}

void SysReadString(char *buffer, int len)
{
  int i = 0;
  char data;
  while (i < len)
  {
    data = kernel->synchConsoleIn->GetChar();
    if (data == '\n')
      break;
    kernel->machine->WriteMem((int)buffer + i, 1, (int)data);
    i++;
  }
}

// void SysReadChar(char *buffer)
// {
//   char data;

//   //get char inputed from "keyboard" to 'data'
//   data = kernel->synchConsoleIn->GetChar();

//   //Record 1 unit (byte) of 'data' into buffer
//   kernel->machine->WriteMem((int)buffer, 1, (int)data);
// }

#endif /* ! __USERPROG_KSYSCALL_H__ */
