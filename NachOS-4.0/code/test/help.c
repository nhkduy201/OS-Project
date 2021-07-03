/* help.c
    CT help dùng để in ra các dòng giới thiệu cơ bản về nhóm 
    và mô tả vắn tắt về chương trình sort và ascii.
*/

#include "syscall.h"

int main()
{
    char* help = ""; 
    help = "|\t\tGroup OS\t\t|\n\
    Members:\n\
    \tNGUYỄN HUỲNH KHÁNH DUY - 19127377\n\
    \tTÔ VŨ THÁI HÀO - 19127391\n\
    \tNGUYỄN QUANG THUẬN -\n\
    \tHỒ THIÊN PHƯỚC-\n\
    \n\
    \t||\t-sort.c-\t//\n\
    *\tTest program to sort a large number of integers.\n\
    *\n\
    *\tIntention is to stress virtual memory system.\n\
    *\n\
    *\tIdeally, we could read the unsorted array off of the file system,\
    *\tand store the result back to the file system!";

    PrintString(help);

    Halt();
    /* not reached */
}