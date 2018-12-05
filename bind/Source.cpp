#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <WinSock2.h>

#pragma comment(lib,"Ws2_32.lib")

int main()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		printf("Error at WSAStartup()!\n");
		WSACleanup();
		return 1;
	}


	SOCKET m_socket;
	m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_socket == INVALID_SOCKET)
	{
		printf("Error at socket()!\n");
		WSACleanup();
		return 1;
	}

	////////////////bind()//////////////////////////////
	// Create a sockaddr_in object and set its values.
	sockaddr_in service;

	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr("127.0.0.1");
	service.sin_port = htons(55555);

	if (bind(m_socket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR)
	{
		printf("bind() fail: %ld. \n", WSAGetLastError());
		closesocket(m_socket);
		WSACleanup();
		return 1;
	}
	else
	{
		printf("bind() is OK!\n");
	}
	WSACleanup();
	return 0;
}