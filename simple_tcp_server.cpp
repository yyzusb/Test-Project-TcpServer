#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#include <WinSock2.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {

	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver,&dat);
	
	//建立服务器端socket;
	SOCKET Tcp_Server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (Tcp_Server == SOCKET_ERROR)
		printf("服务器建立socket失败...\n");
	else
		printf("服务器建立socket成功!\n");

	//bind绑定端口;
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(4567);
	_sin.sin_addr.S_un.S_addr = INADDR_ANY;
	if (SOCKET_ERROR == bind(Tcp_Server, (sockaddr*)&_sin, sizeof(_sin)))
		printf("绑定端口失败...\n");
	else
		printf("绑定端口成功!\n");

	//监听端口;
	if(SOCKET_ERROR == listen(Tcp_Server, 5))
		printf("监听端口失败...\n");
	else
		printf("监听端口成功!\n");

	//等待接受客户端;
	sockaddr_in _client_addr = {};
	int nClientAddr = sizeof(_client_addr);
	SOCKET client_socket = INVALID_SOCKET;
	client_socket = accept(Tcp_Server, (sockaddr*)&_client_addr, &nClientAddr);
	if (client_socket == INVALID_SOCKET)
		printf("无效的客户端...\n");
	else
		printf("客户端连接成功,socket=%d, IP=%s\n", (int)client_socket,inet_ntoa(_client_addr.sin_addr));
	
	//接受客户端数据，并处理
	char rev_buf[128];
	char name[] = "bill";
	char age[] = "18";
	while (true) {
		int nLen = recv(client_socket, rev_buf, 128, 0);
		if (nLen <= 0) {
			printf("客户端已经退出\n");
			break;
		}
		printf("接受客户端数据:%s\n", rev_buf);
		if (strcmp(rev_buf, "name") == 0)
			send(client_socket, name, strlen(name) + 1, 0);
		else if (strcmp(rev_buf, "age") == 0)
			send(client_socket, age, strlen(age) + 1, 0);
		else
			send(client_socket, rev_buf, strlen(rev_buf) + 1, 0);
	}
	//关闭socket
	closesocket(Tcp_Server);


	getchar();
	WSACleanup();

	return 0;
}
