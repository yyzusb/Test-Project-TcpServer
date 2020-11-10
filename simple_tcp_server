#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#include <WinSock2.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {

	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver,&dat);
	
	//1、建立服务器端socket;
	SOCKET Tcp_Server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (Tcp_Server == SOCKET_ERROR)
		printf("建立socket失败...\n");
	else
		printf("建立socket成功!\n");

	//2、bind绑定端口;
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(4567);
	_sin.sin_addr.S_un.S_addr = INADDR_ANY;
	if (SOCKET_ERROR == bind(Tcp_Server, (sockaddr*)&_sin, sizeof(_sin)))
		printf("绑定端口失败...\n");
	else
		printf("绑定端口成功!\n");

	//3、监听端口;
	if(SOCKET_ERROR == listen(Tcp_Server, 5))
		printf("监听端口失败...\n");
	else
		printf("监听端口成功!\n");

	//4、等待接受客户端;
	sockaddr_in _client_addr = {};
	int nClientAddr = sizeof(_client_addr);
	char buf_msg[256] = "Tcp Server";
	SOCKET clientsocket = INVALID_SOCKET;
	while (true) {
		clientsocket = accept(Tcp_Server, (sockaddr*)&_client_addr, &nClientAddr);
		if (clientsocket == INVALID_SOCKET)
			printf("无效的客户端...\n");
		else
			printf("客户端连接成功 IP=%s\n", inet_ntoa(_client_addr.sin_addr));

		//5、send向客服端发送数据；
		send(clientsocket, buf_msg, strlen(buf_msg) + 1, 0);
	}
	//6、关闭socket
	closesocket(Tcp_Server);

	WSACleanup();
	return 0;
}
