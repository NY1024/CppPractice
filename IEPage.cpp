#include "stdafx.h"
#include <stdio.h>
void CreatStringReg(HKEY hRoot,char *szSubKey,char* valueName,char *Data)
{
HKEY hKEY;
long lRet=RegCreateKeyEx(hRoot,szSubKey,0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&hKEY,NULL);
	if (lRet != ERROR_SUCCESS)
	{
		printf("*error no RegCreateKeyEx %s\n",szSubKey);
	}
lRet=RegSetValueEx(hKey,ValueName,0,REG_SZ,(BYTE*)Data,strlen(Data));
if (lRet != ERROR_SUCCESS)
{
	printf(*error no RegSetValueEx %s\n",ValueName);
		return;
}
RegCloseKey(hKey);
}
int APIENTRY WinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
				     LPSTR lpCmdLine
					 int nCmdShow)
{
	char StartPage[255]="http://www.sina.com/";
	CreateStringReg(HKEY_CURRENT_USER,"Software\\Microsoft\\Internet Explorer\\Main","Start Page",StartPage);
	return 0;
}
