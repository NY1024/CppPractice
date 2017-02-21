#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
struct Dirlist{
	char table[256];
	Dirlist *pNext;
};
Dirlist *first,*newlist,*last;
void AddList(char *list)
{
	newlist=new DirList;
	strcpy(newlist->table,list);
	newlist->pNext=NULL;
	if(first==NULL)
	{
		first=newlist;
		last=newlist;
	}
	else
	{
		last->pNext=newlist;
		last=newlist;
	}
}
void FindFile(char *pRoad,char *pFile)
{
	char FileRoad[256]={0};
	char DirLoad[256]={0};
	char FindedFile[256]={0};
	char FindedDir[256]={0};
	strcpy{FileRoad,pRoad};
	strcpy{DirRoad,pRoad};
	strcat(DirRoad,"\\*.*");
	WIN32_FIND_DATA findData;
	HANDLE hFindFile;
	hFindFile=FindFirstFile(DirRoad,&findData);
	if(hFindFile!=INVALID_HANDLE_VALUE)
	{
		do
		{
			if(findData.cFileName[0]=='.')
				continue;
			if(findData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
			{
				strcpy(FindedDir,pRoad);
				strcat(FindedDir,"\\");
				strcat(FindedDir,findData.cFileName);
				Addlist(FindedDir);
				memset(FindedDir,0x00,256);

			}

		}
		while(FindNextFile(hFindFile,&findData));
	}
	strcat(FileRoad,"\\");
	strcat(FileRoad,pFile);
	hFindFile=FindFirstFile(FileRoad,&findData);
	if(hFindFile!=INVALID_HANDLE_VALUE)
	{
		do
		{
			strcpy(FindedFile,pRoad);
			strcat(FindedFile,"\\");
			strcat(FindedFile,findData,cFileName);
			printf("%s\n",FindedFile );
			memset(FindedFile,0x00,256);

		}while(FindNextFile(hFindFile,&findData));
	}
}
int SearchFile(char *Directory,char *SearchFile)
{
	Dirlist NewList;
	strcpy(NewList.table,Directory);
	NewList.pNext=NULL;
	last=&NewList;
	first=&NewList;
	while(true)
	{
		DirList *Find;
		if(first!=NULL)
		{
			Find=first;
			first=forst->pNext;
			FindFile(Find->table,SearchFile);
		}
		else
		{
			printf("文件搜索完毕\n");
			return 0;
		}
	}
	return 0;
}
int main(int argc,char/ argv[])
{
	SearchFile(argv[1],argv[2]);
	return 0;
}