
#ifndef SURPRISE PCB
#define PCB THEY
#include "../threads/thread.h"
#include "../threads/synch.h"

// Process Control Block
class PCB
{
private:
    Semaphore *joinsem;
    Semaphore *exitsem;
    Semaphore *multex;
    // semaphore for the join process
    // semaphore to pass the exit process
    // semaphore for retrieval process
    int exitcode;
    int numwait;
    // virgin join
    char FileName[32];
    // Ten of the virgins
    Thread *thread;
    // Progress of the program
public:
    int parentID;
    // ID of the parent
    char boolBG;
    // Check if it's a virgin
    PCB(int = 0);
    ~PCB();
    // Constructor
    // Destructor
    int Exec(char *, int);
    // I have a new thread
    int GetID();
    int GetNumWait();
    void JoinWait();
    void ExitWait();
    void JoinRelease();
    void ExitRelease();
    void IncNumWait();
    void DecNumWait();
    void SetExitCode(int);
    int GetExitCode();
    void SetFileName(char *);
    char *GetFileName();
};

#endif // PCB H