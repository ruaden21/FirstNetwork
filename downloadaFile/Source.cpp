#include <tchar.h>
#include <urlmon.h>
#include <shellapi.h>
#include <stdio.h>

#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "urlmon.lib")

#define BUFSIZE 260


int main(int argc, char **argv)
{
	///*HRESULT hr1 = URLDownloadToFile(NULL, _T("http://unikey.vn/download/201807/UniKey-4.2RC4-140823-Setup_x64.exe"), _T("C:\\Users\\NOKIA\\Desktop\\x.exe"), 0, NULL);
	//Sleep(500);
	//HINSTANCE hr2 = ShellExecuteA(NULL, "open", "C:\\Users\\NOKIA\\Desktop\\x.exe", NULL, NULL, SW_SHOW);*/
	
	char currentFile[BUFSIZE];
	char dest[BUFSIZE];
	char *pResult;
	char *nameFile = "download.exe";
	//char deleteFile[BUFSIZE];
	char *deleteFile;

	char c;

	GetModuleFileNameA(NULL, currentFile, BUFSIZE);
	strcpy(dest,"C:\\Users\\NOKIA\\Desktop\\");

	
	pResult = strstr(currentFile, dest);
	if (pResult == 0)
	{
		strcat(dest, nameFile); //		\dest\nameFile
		CopyFileA(currentFile, dest, FALSE);
		ShellExecuteA(NULL, "open", dest, currentFile, NULL, SW_SHOW);
		return 0;
	}
	Sleep(2000);
	deleteFile = GetCommandLineA();
	deleteFile = strstr(deleteFile,".exe\" ");
	deleteFile = deleteFile + 6;
	//strcpy(deleteFile,argv[1]);
	DeleteFileA(deleteFile);
	printf("***********\n");
	printf("%s\n", deleteFile);
	printf("***********\n");

	c = getchar();

	return 0;
}