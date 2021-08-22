// exception.cc
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "main.h"
#include "synchconsole.h"
#include "syscall.h"
#include "ksyscall.h"
#include "console.h"
#include "thread.h"
#include "synch.h"
#include "sysdep.h"

//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2.
//
// If you are handling a system call, don't forget to increment the pc
// before returning. (Or else you'll loop making the same system call forever!)
//
//	"which" is the kind of exception.  The list of possible exceptions
//	is in machine.h.
//----------------------------------------------------------------------

void IncreasePC()
{
	{
		/* set previous programm counter (debugging only)*/
		kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));

		/* set programm counter to next instruction (all Instructions are 4 byte wide)*/
		kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);

		/* set next programm counter for brach execution */
		kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg) + 4);
	}
}

void ExceptionHandler(ExceptionType which)
{
	int type = kernel->machine->ReadRegister(2);

	DEBUG(dbgSys, "Received Exception " << which << " type: " << type << "\n");

	switch (which)
	{
	// Handle function written for user system calls
	case SyscallException:
		switch (type)
		{
		case SC_Exec:
			// Input: vi tri int
			// Output: Fail return -1, Success: return id cua thread dang chay
			// SpaceId Exec(char *name);
			int virtAddr;
			virtAddr = machine->ReadRegister(4);	// doc dia chi ten chuong trinh tu thanh ghi r4
			char* name;
			name = User2System(virtAddr, MaxFileLength + 1); // Lay ten chuong trinh, nap vao kernel
	
			if(name == NULL)
			{
				DEBUG('a', "\n Not enough memory in System");
				printf("\n Not enough memory in System");
				machine->WriteRegister(2, -1);
				//IncreasePC();
				return;
			}
			OpenFile *oFile = fileSystem->Open(name);
			if (oFile == NULL)
			{
				printf("\nExec:: Can't open this file.");
				machine->WriteRegister(2,-1);
				IncreasePC();
				return;
			}

			delete oFile;

			// Return child process id
			int id = pTab->ExecUpdate(name); 
			machine->WriteRegister(2,id);

			delete[] name;	
			IncreasePC();
			return;
// 			DEBUG(dbgSys, "Exec");
// 			int virtAddr;
// 			virtAddr = kernel->machine->ReadRegister(4);
// 			char buf[255];
// 			bzero(buf, 255);
// 			sprintf(buf, "p%d", processID );
// 			Thread* mythread;
// 			// I
// 			mythread = new Thread(buf);
// 			mythread->processID  = processID++;
// 			kernel->machine->ReadRegister(4) << "\n";
// 			mythread->space=kernel->currentThread->space;
// 			/*j mythread->SaveUserState();
// 			kernel->currentThread->SelfTest();
// 			//kernel->currentThread=thread;
// 			// mythread->Fork((VoidFunctionPtr) SimpleThread, (void *) 1);
// 			// kernel->currentThread->Yield();
// 			// kernel->machine->WriteRegister(2,processID -1);
// 			Modify return point */
// 			IncreasePC()
// 			break;
		case SC_Halt:
			DEBUG(dbgSys, "Shutdown, initiated by user program.\n");

			SysHalt();

			ASSERTNOTREACHED();
			break;

		case SC_Add:
		{
			DEBUG(dbgSys, "Add " << kernel->machine->ReadRegister(4) << " + " << kernel->machine->ReadRegister(5) << "\n");
			/* Process SysAdd Systemcall*/
			int result;
			result = SysAdd(/* int op1 */ (int)kernel->machine->ReadRegister(4),
											/* int op2 */ (int)kernel->machine->ReadRegister(5));
			DEBUG(dbgSys, "Add returning with " << result << "\n");
			/* Prepare Result */
			kernel->machine->WriteRegister(2, (int)result);
			IncreasePC();
			return;
		}
			ASSERTNOTREACHED();

			break;

		case SC_ReadNum:
		{
			int num = 0;
			int sign = 1;
			int i = 0;
			char c, maybeSign;
			maybeSign = kernel->synchConsoleIn->GetChar();
			if (maybeSign == '-')
			{
				sign = -1;
				i++;
			}
			else
			{
				num = maybeSign - '0';
			}
			while (true)
			{
				c = kernel->synchConsoleIn->GetChar();
				if (c == '\n')
					break;
				num = num * 10 + (c - '0');
				i++;
			}
			num *= sign;
			kernel->machine->WriteRegister(2, num);
			// Debug
			DEBUG(dbgSys, "The number readed: " << num << "\n");
			IncreasePC();
			return;
		}
		break;

		case SC_PrintNum:
			DEBUG(dbgSys, "Print a integer: " << kernel->machine->ReadRegister(4) << "\n");
			SysPrintNum((int)kernel->machine->ReadRegister(4));
			IncreasePC();
			return;
			break;

		case SC_ReadString:
		{
			DEBUG(dbgSys, "Read a string\n");
			SysReadString((char *)kernel->machine->ReadRegister(4), (int)kernel->machine->ReadRegister(5));
			// Debug
			int c, cnt;
			cnt = 0;
			while (true)
			{
				kernel->machine->ReadMem(kernel->machine->ReadRegister(4) + cnt++, 1, &c);
				if (char(c) == '\0')
				{
					break;
				}

				DEBUG(dbgSys, char(c));
			}

			IncreasePC();
			return;
		}
		break;

		case SC_ReadChar:
			//Input: none
			//Output: 1 char
			//Usage: Read a character inputed by user
			{
				DEBUG(dbgSys, "Read a character:\n");

				//Read the char into a value
				char c = kernel->synchConsoleIn->GetChar();

				//write to register
				kernel->machine->WriteRegister(2, c);
				// Debug
				DEBUG(dbgSys, "The char readed: " << char(c));

				IncreasePC();
				return;
			}
			break;

		case SC_PrintChar:
			kernel->synchConsoleOut->PutChar(kernel->machine->ReadRegister(4));

			IncreasePC();
			return;

		case SC_PrintString:
		{
			int vaddr = kernel->machine->ReadRegister(4);
			int memval;

			kernel->machine->ReadMem(vaddr, 1, &memval);
			while ((*(char *)&memval) != '\0')
			{

				kernel->synchConsoleOut->PutChar(*(char *)&memval);
				vaddr++;

				kernel->machine->ReadMem(vaddr, 1, &memval);
			}

			IncreasePC();
			return;
		}
		break;

		case SC_RandomNum:
		{
			int random = (int)RandomNumber();
			kernel->machine->WriteRegister(2, random);

			DEBUG(dbgSys, "The random number: " << random);

			IncreasePC();
			return;
		}
		break;

		default:
			cerr << "Unexpected system call " << type << "\n";
			break;
		}
		break;
	// Returns control to the OS
	case NoException:
		return;
	// Other exception, display an error message and halt system
	default:
		DEBUG(dbgSys, "Unexpected user mode exception" << (int)which << "\n");
		cerr << "Unexpected user mode exception" << (int)which << "\n";
		SysHalt();
		break;
	}
	ASSERTNOTREACHED();
}
