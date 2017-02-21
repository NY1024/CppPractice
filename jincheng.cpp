#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <tlhelp32.h>
int KillProcess(DWORD Pid)
{
	HANDLE hProcess=OpenProcess(PROCESS_ALL_ACCESS,FALSE,Pid);
	if(hProcess==NULL)
	{
		printf("OpenProcess error\n");
		return 0; 
	}
	if (TerminateProcess(hProcess,0))
	{
		printf("结束进程成功\n");
		return 0;
	}
	else
	{
		printf ("结束进程失败\n");
		return 0;
	}
}
int GetProcess()
{
	char buff[1024]={0};
	PROCESSENTRY32 pe32;
	pe32.dwSize=sizeof(pe32);
	HANDLE hProcessSnap=CreateToolHelp32Snapshot(TH32CS_SNAPPROCESS,0);
	if (hProcessSnap==INVALID_HANDLE_VALUE)
	{
		printf ("CreateToolHelp32Snapshot error");
		return 0;
	}
BOOL bPROCESS=Process32First(hProcessSnap,&pe32);
while(bProcess)
{
	wsprintf(buff,"%s------%d\r\n",pe32,szExeFile,pe32.th32ProcessID);
	printf(buff);
	memset(buff,0x00,1024)
	bProcess=Process32Next(hProcessSnap,&pe32);

}
CloseHandle(hProcessSnap);
return 0;
}
int main(int argc,char* atgv[])
{
	if(argc==2&&strcmp(argv[1],"list")==0)
	{
		GetProcess();
	}
	if(argc==3&&strcmp(argv[1],"kill")==0)
	{
		KillProcess(atoi(argv[2]));
	}
	return 0;
}