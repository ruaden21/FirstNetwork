#include <stdio.h>
#include <winsock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")
#define PORT "80"


int main()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	char request[] = "GET /pro113ti/Thuc-tap-nhom/master/New folder/New Text Document.txt HTTP/1.0\r\n\r\n";
	//	char host[] = "archive.4plebs.org";
	char host[] = "raw.githubusercontent.com";


	wVersionRequested = MAKEWORD(2, 2);

	FILE *downloadFile;
	downloadFile = fopen("download.txt", "w+");
	if (downloadFile == NULL)
	{
		printf("open failed\n");
		return 1;
	}
	printf("OPENED FILE!\n");

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

	

	addrinfo *result = NULL, *ptr = NULL, hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	err = getaddrinfo(host, PORT, &hints, &result);
	if (err != 0) {
		printf("getaddrinfo failed with error: %d\n", err);
		WSACleanup();
		return 1;
	}

	SOCKET m_socket = INVALID_SOCKET;
	
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next)
	{
		m_socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (m_socket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			return 1;
		}

		//Connect to server
		err = connect(m_socket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (err == SOCKET_ERROR)
		{
			closesocket(m_socket);
			m_socket = INVALID_SOCKET;
			continue;
		}
		printf("CONNECTED\n");
		break;
	}
	
	err = send(m_socket, request, (int)strlen(request), 0);
	if (err == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(m_socket);
		WSACleanup();
		return 1;
	}
	printf("SENDED REQUEST!\n");

	char recivedBuff[1000] = {0};
	int i = 0;
	do
	{
		ZeroMemory(recivedBuff, 1000);
		err = recv(m_socket, recivedBuff, 1000, 0);
		if (err == SOCKET_ERROR) {
			printf("recv failed with error: %d\n", WSAGetLastError());
			closesocket(m_socket);
			WSACleanup();
			return 1;
		}
		// printf("RECIVED OK!\n");

		fprintf(downloadFile, recivedBuff);
		/*if (err < 0)
		{
			printf("writing file failed\n");
			closesocket(m_socket);
			WSACleanup();
			return 1;
		}*/
		// printf("Size of file is %u ", err);
		++i;
	} while (err != 0);

	fclose(downloadFile);

	// clean up
	closesocket(m_socket);
	WSACleanup();
	return 0;
}