/* help.c
    CT help dùng để in ra các dòng giới thiệu cơ bản về nhóm 
    và mô tả vắn tắt về chương trình sort và ascii.
*/

#include "syscall.h"

int main()
{
    char* help = ""; 
    help = "\\\\\t-sort.c-\t//\n\
    *\tTest program to sort a large number of integers.\n\
    *\n\
    *\tIntention is to stress virtual memory system.\n\
    *\n\
    *\tIdeally, we could read the unsorted array off of the file system,\
    *\tand store the result back to the file system!";

    PrintString(help,6);

    Halt();
    /* not reached */
}