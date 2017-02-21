DWORD WINAPI ThreadA( LPVOID lpParam)
{
	SECURITY_ATTRUBYTES sa;
	DWORD nByteToWrite,nByteToWritten;
	char  recv_buff[1024];
	sa.nLength = sizeof(SECURITY_ATTRUBYTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	CreatePipe(&hReadPipe,&hWriteFile,&sa,0);
	while(true)
	{
		Sleep(250);
		nByteToWrite = recv(sClient,recv_buff,1024,0);
		WriteFile(hWriteFile,recv_buff,nByteToWrite,&nByteToWritten,NULL);

	}
	return 0;
}

DWORD WINAPI ThreadA (LPVOID lpParam)
{
	SECURITY_ATTRUBYTES sa;
	DWORD len;
	char send_buff[2048];
	sa.nLength = sizeof(SECURITY_ATTRUBYTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
		CreatePipe(&hReadFile,&hWritePipe,&sa,0);
	while (true)
	{
		ReadFile(hReadFile,send_buff,2048,&len,NULL);
		send(sClient,send_buff,len,0);

	}
	return 0;
}
