#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
int main (int argc,char* atgv[])
{
HANDLE hFile=CreateFile(argv[2],GENERIC_WRITE,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
if(hFile==INVALID_HANDLE_VALUE)
{
	printf("CreateFile erroe\n");
	return 0;
}
if (SetFilePointer(hFile,0,NULL,FILE_END)==-1)
{
	printf(*SetFilePointer error \n");
	return 0;
}

char buff[256]="配置信息";
DWORD dwWrite;
if(!WriteFile(hFile,&buff,strlen(buff),&dwWrite,NULL))
{
	printf("WriteFile error \n")
	return 0;
}
printf ("往%s中写入数据成功\n",argv[1]);
ClosedHandle(hFile);
return 0;
}