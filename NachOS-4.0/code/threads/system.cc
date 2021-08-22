#include "copyright.h"
#include "kernel.h"

Thread *currentThread;
Thread *threadToBeDestroyed;
Scheduler *scheduler;
Interrupt *interrupt;
Statistics *stats;
Timer *timer;

#ifdef FILESYS_NEEDED
FileSystem *fileSystem;
#endif

#ifdef FILESYS
SynchDisk *synchDisk;
#endif

#ifdef USER_PROGRAM
Machine *machine;
SynchConsole *gSynchConsole;

Semaphore *addrLock;
BitMap *gPhysPageBitMap;
PTable *pTab;
STable *semTab;
#endif

#ifdef NETWORK
PostOffice *postOffice;
#endif

extern void Cleanup();

static void
TimerInterruptHandler(int dummy)
{
    if (interrupt->getStatus() != IdleMode)
        interrupt->YieldOnReturn();
}
void Initialize(int argc, char **argv)
{
    int argCount;
    char *debugArgs = "";
    bool randomYield = FALSE;

#ifdef USER_PROGRAM
    bool debugUserProg = FALSE;
#endif
#ifdef FILESYS_NEEDED
    bool format = FALSE;
#endif
#ifdef NETWORK
    double rely = 1;
    int netname = 0;
#endif

    for (argc--, argv++; argc > 0; argc -= argCount, argv += argCount)
    {
        argCount = 1;
        if (!strcmp(*argv, "-d"))
        {
            if (argc == 1)
                debugArgs = "+";
            else
            {
                debugArgs = *(argv + 1);
                argCount = 2;
            }
        }
        else if (!strcmp(*argv, "-rs"))
        {
            ASSERT(argc > 1);
            RandomInit(atoi(*(argv + 1)));
            randomYield = TRUE;
            argCount = 2;
        }
#ifdef USER_PROGRAM
        if (!strcmp(*argv, "-s"))
            debugUserProg = TRUE;
#endif
#ifdef FILESYS_NEEDED
        if (!strcmp(*argv, "-f"))
            format = TRUE;
#endif
#ifdef NETWORK
        if (!strcmp(*argv, "-l"))
        {
            ASSERT(argc > 1);
            rely = atof(*(argv + 1));
            argCount = 2;
        }
        else if (!strcmp(*argv, "-m"))
        {
            ASSERT(argc > 1);
            netname = atoi(*(argv + 1));
            argCount = 2;
        }
#endif
    }

    DebugInit(debugArgs);
    stats = new Statistics();
    interrupt = new Interrupt;
    scheduler = new Scheduler();
    if (randomYield)
        timer = new Timer(TimerInterruptHandler, 0, randomYield);

    threadToBeDestroyed = NULL;
    currentThread = new Thread("main");
    currentThread->setStatus(RUNNING);

    interrupt->Enable();
    CallOnUserAbort(Cleanup);

#ifdef USER_PROGRAM
    machine = new Machine(debugUserProg);
    gSynchConsole = new SynchConsole();

    addrLock = new Semaphore("addrLock", 1);
    gPhysPageBitMap = new BitMap(256);
    pTab = new PTable(10);
    semTab = new STable();
#endif

#ifdef FILESYS
    synchDisk = new SynchDisk("DISK");
#endif

#ifdef FILESYS_NEEDED
    fileSystem = new FileSystem(format);
#endif

#ifdef NETWORK
    postOffice = new PostOffice(netname, rely, 10);
#endif
}
void Cleanup()
{
    printf("\nCleaning up...\n");
#ifdef NETWORK
    delete postOffice;
#endif

#ifdef USER_PROGRAM
    delete machine;
    delete gSynchConsole;

#endif

#ifdef FILESYS_NEEDED
    delete fileSystem;
#endif

#ifdef FILESYS
    delete synchDisk;
#endif

    delete timer;
    delete scheduler;
    delete interrupt;

    Exit(0);
}
