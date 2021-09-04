/////////////////////////////////////////////////
// 	DH KHTN - DHQG TPHCM			/
// 	NGUYỄN HUỲNH KHÁNH DUY - 19127377
//	TÔ VŨ THÁI HÀO - 19127391
//	NGUYỄN QUANG THUẬN - 19127571
//	HỒ THIÊN PHƯỚC- 19127517		/
/////////////////////////////////////////////////

#include "syscall.h"


void main()
{
	int pingPID, pongPID;
	PrintString("Ping-Pong test starting...\n\n");
	pingPID = Exec("./test/ping");
	pongPID = Exec("./test/pong");
	Join(pingPID);
	Join(pongPID);	
}
