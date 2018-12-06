#include <tchar.h>
#include <urlmon.h>
#include <shellapi.h>


#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "urlmon.lib")
int main()
{
	/*HRESULT hr1 = URLDownloadToFile(NULL, _T("http://unikey.vn/download/201807/UniKey-4.2RC4-140823-Setup_x64.exe"), _T("C:\\Users\\NOKIA\\Desktop\\x.exe"), 0, NULL);
	Sleep(500);*/
	HINSTANCE hr2 = ShellExecuteA(NULL, "open", "C:\\Users\\NOKIA\\Desktop\\x.exe", NULL, NULL, SW_SHOW);
	DeleteFileA("C:\\Users\\NOKIA\\Desktop\\x.exe");
	return 0;
}