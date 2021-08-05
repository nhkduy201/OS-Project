#ifndef SYSTEM_H
#define SYSTEM_H

#include "copyright.h"
#include "utility.h"
#include "thread.h"
#include "scheduler.h"
#include "interrupt.h"
#include "stats.h"
#include "timer.h"
#include "bitmap.h"
#include "ptable.h"
#include "stable.h"

extern void Initialize(int argc, char **argv);
extern void Cleanup();

extern Thread *currentThread;
extern Thread *threadToBeDestroyed;
extern Scheduler *scheduler;
extern Interrupt *interrupt;
extern Statistics *stats;
extern Timer *timer;

#ifdef USER_PROGRAM
#include "machine.h"
#include "synchcons.h"
#include "synch.h"
extern Machine *machine;
extern SynchConsole *gSynchConsole;

extern Semaphore *addrLock;
extern BitMap *gPhysPageBitMap;
extern PTable *pTab;
extern STable *semTab;
#endif

#ifdef FILESYS_NEEDED
#include "filesys.h"
extern FileSystem *fileSystem;
#endif

#ifdef FILESYS
#include "synchdisk.h"
extern SynchDisk *synchDisk;
#endif

#ifdef NETWORK
#include "post.h"
extern PostOffice *postOffice;
#endif

#endif // SYSTEM_H
