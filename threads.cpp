#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
HANDLE hFile;
CRITICAL_SECTION cs;
DWORD WINAPI Thread{LPVOID lpParam}
{
	int n=(int)lpParam;
	DWORD dwWrite;
	for (int i=0;i<10000;i++)
	{
		EnterCriticalSection(&cs);
		char Data[512]="--------------------------------------------------------";
		WriteFile(hFile,&Data,strlen(Data),&dwWrite,NULL);
		LeaveCriticalSection(&cs);
	}
	printf("第%d号线程结束运行\n",n);
	return 0;
} 
int main(int argc,char*,argv[])
{
	hFile=CreateFile("hack.txt",GENERIC_WRITE,0,NULL,CREATE)ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile==INVALID_HANDLE_VALUE)
	{
		printf("CreateFile Error\n");
		return 0;
	}
	DWORD ThreadId;
	HANDLE hThread[5];
	InitializeCriticalSection(&cs);
	for(int i=0;i<5;i++)
	{
		hThread[i]=CreateThread(NULL,NULL,Thread,LPVOID(i+1),0.&ThreadId);
		printf("第%d号线程创建成功\n",i+1 );
	}
	WaitForMultipleObjects(5,hThread,true,INFINITE);
	DeleteCriticalSection(&cs);
	ClosedHandle(hFile);
	return 0;
}