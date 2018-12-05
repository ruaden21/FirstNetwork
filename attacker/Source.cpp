#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

#define FUNNY_STUFF "NAH THING HERE !"

int __cdecl main(void)
{
	WSADATA wsaData;
	int iResult;

	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;

	struct addrinfo *result = NULL;
	struct addrinfo hints;

	int iSendResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	// Create a SOCKET for connecting to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	freeaddrinfo(result);

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	while (1)
	{
		// Accept a client socket
		ClientSocket = accept(ListenSocket, NULL, NULL);
		if (ClientSocket == INVALID_SOCKET) {
			printf("accept failed with error: %d\n", WSAGetLastError());
			closesocket(ListenSocket);
			WSACleanup();
			return 1;
		}
		else
		{
			printf("A STRANGE MAN HAS CONNECTED\n");
		}

		ZeroMemory(recvbuf, recvbuflen);
		iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0)
		{
			char buffer[DEFAULT_BUFLEN];
			strcpy(buffer, recvbuf);
			printf("JERRY: %s\n", buffer);

			if (!strcmp(buffer, "!ALOALOCHIMSEGOIDAIBANG"))
			{
				char *sendbuf = "!DAIBANGNGHEROALOALO";
				iSendResult = send(ClientSocket, sendbuf, (int)strlen(sendbuf), 0);
				if (iSendResult == SOCKET_ERROR)
				{
					printf("send failed with error: %d\n", WSAGetLastError());
					closesocket(ClientSocket);
					WSACleanup();
					return 1;
				}
				printf("\n\n\n\tCommand table: \n1. PRINT HELLO WORLD\n2. CLOSE THE JERRY UNTIL THE NEXT BOOT\n");

				while (1)
				{
					char iChoice[2];
					// More check here please man
					printf("TOM: ");
					scanf("%s", &iChoice);
					/*if (iChoice - '0' > 9 || iChoice - '0' < 0)
					{
						continue;
					}*/
					iSendResult = send(ClientSocket, iChoice, (int)strlen(sendbuf), 0);
					if (iSendResult == SOCKET_ERROR)
					{
						printf("send failed with error: %d\n", WSAGetLastError());
						closesocket(ClientSocket);
						WSACleanup();
						return 1;
					}
					ZeroMemory(recvbuf, recvbuflen);
					iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
					if (iResult > 0)
					{
						ZeroMemory(buffer, recvbuflen);
						strcpy(buffer, recvbuf);
						printf("JERRY: %s\n", buffer);
					}
					if (iChoice[0] == '2')
					{
						break;
					}
				}

			}
			else
			{
				printf("WORNG PASSWORD.\nEXIT\n");
			}
		}

	}
	// cleanup
	closesocket(ListenSocket);
	closesocket(ClientSocket);
	WSACleanup();

	return 0;
}