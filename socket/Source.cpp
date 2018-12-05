#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	
	wVersionRequested = MAKEWORD(2, 2);

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		printf("DLL isn't found\n");
		WSACleanup();
		return 1;
	}
	else
	{
		printf("The Winsock DLL found!\n");
		printf("The status: %s.\n", wsaData.szSystemStatus);
	}

	SOCKET m_socket = INVALID_SOCKET;
	m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_socket == INVALID_SOCKET)
	{
		printf("Error at socket(): %ld\n", WSAGetLastError());
	}
	else
	{
		printf("socket() is OK!\n");
	}

	WSACleanup();
	return 0;
}