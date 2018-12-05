#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib,"ws2_32.lib")

int main()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(2, 2);

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		printf("WSAStartup failed with error: %d\n", err);
		return 1;
	}
	
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		printf("Could not find a usable version of Winsock.dll\n");
		WSACleanup();
		return 1;
	}
	else
	{
		printf("The current version is %u.%u\n", LOBYTE(wsaData.wVersion), HIBYTE(wsaData.wVersion));
		printf("The highest version is %u.%u\n", LOBYTE(wsaData.wHighVersion), HIBYTE(wsaData.wHighVersion));
	}
	
	WSACleanup();
	return 0;
}
