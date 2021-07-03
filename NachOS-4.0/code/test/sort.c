/* sort.c 
 *    Test program to sort a large number of integers.
 *
 *    Intention is to stress virtual memory system.
 *
 *    Ideally, we could read the unsorted array off of the file system,
 *	and store the result back to the file system!
 */


/*
#define UNIX
#define UNIX_DEBUG
*/

#ifdef UNIX
#include <stdio.h>
#define Exit exit
#else
#include "syscall.h"
#endif /* UNIX */

#define SIZE (1024)

int A[SIZE];	/* size of physical memory; with code, we'll run out of space!*/

int
main()
{
    int n;
    int tmp;

    PrintString("enter n: \n",11);
    n = ReadNum();

    for (int i = 0; i < n; i++)
    {
        /* code */
        PrintString("A[",3);
        PrintNum(i);
        PrintString("]: \n",1);
        A[i] = ReadNum();
    }
    
    char arr[1];

    PrintString("enter < or >", 13);

    arr[0] = ReadChar();

    /* then sort! */
    
    if (arr[0] = '<')
    {
        /* code */
        for (int q = 0; q < n; q++) {
        for (int w = 0; w < (n-1); w++) 
        {
	        if (A[w] < A[w + 1]) 
            {	/* out of order -> need to swap ! */
	            tmp = A[w];
	            A[w] = A[w + 1];
	            A[w + 1] = tmp;
    	    }
        }
        }
    }
    else
    {
        for (int k = 0; k < n; k++) {
        for (int l = 0; l < (n-1); l++) {
	   if (A[l] > A[l + 1]) {	/* out of order -> need to swap ! */
	      tmp = A[l];
	      A[l] = A[l + 1];
	      A[l + 1] = tmp;
    	   }
        }
        }
    }
    

#ifdef UNIX_DEBUG
    for (i=0; i<SIZE; i++) {
        printf("%4d ", A[i]);
	if (((i+1) % 15) == 0) {
		printf("\n");
        }
        if (A[i] != i) {
            fprintf(stderr, "Out of order A[%d] = %d\n", i, A[i]);
            Exit(1);
        }   
    }
    printf("\n");
#endif /* UNIX_DEBUG */

    for (int h=0; h<n; h++) {
        if (A[h] != h) {
            Exit(1);
        }   
    }

    Exit(0);
}
