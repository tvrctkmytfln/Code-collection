#include<winsock2.h>
#include<stdio.h>
#pragma comment(lib, "ws2_32.lib")
#define PORT 6013
#define IP "172.30.58.113"
int main(void)
{
	int Condition;
//����Դ�ļ�����
	FILE *fsource;
	fsource = fopen("C:\\Users\\Administrator\\Desktop\\The Little Prince.txt", "r");
	if (fsource == NULL)
	{
		puts("�����ļ���ʧ��,��������˳�");
		getchar();
		exit(-1);
	}
	puts("===================�ļ��򿪳ɹ�===================\n\n");
//�����׽���
	WSADATA wsaData;
	SOCKET socket_Server;
	SOCKADDR_IN addrServer;
	SOCKET socket_Client;
	SOCKADDR_IN addrClient;
	Condition = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (Condition != 0)
	{
		puts("����Windows Socket API ����ʧ�ܣ���������˳�");
		getchar();
		exit(-1);
	}
	socket_Server = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_Server == INVALID_SOCKET)
	{
		puts("����SOCKET ����ʧ�ܣ���������˳�");
		WSACleanup();
		getchar();
		exit(-1);
	}
	addrServer.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(PORT);
	Condition = bind(socket_Server, (SOCKADDR*)&addrServer, sizeof(SOCKADDR));
	if (Condition == SOCKET_ERROR)
	{
		puts("����socket_Server��ʧ�ܣ���������˳�");
		closesocket(socket_Server);
		WSACleanup();
		getchar();
		exit(-1);
	}
	puts("=================WSA,socket�����ɹ�===============\n\n");
//������������
	Condition = listen(socket_Server, 5);
	if (Condition == SOCKET_ERROR)
	{
		puts("����������������ʧ�ܣ���������˳�");
		closesocket(socket_Server);
		WSACleanup();
		getchar();
		exit(-1);
	}
	puts("================����������������......============\n\n");
	int len = sizeof(SOCKADDR);
	char send_massage[100] = "���Է��������Ѿ����ӵ�������";
	char recvBuf[100];
	socket_Client = accept(socket_Server, (SOCKADDR*)&addrClient, &len);
	if (socket_Client == INVALID_SOCKET)
	{
		puts("�������ӵ��ͻ���ʧ�ܣ���������˳�");
		closesocket(socket_Server);
		WSACleanup();
		getchar();
		exit(-1);
	}
	send(socket_Client, send_massage, strlen(send_massage) + 1, 0);
	recv(socket_Client, recvBuf, 100, 0);
	printf("%s\n", recvBuf);
	char Send_File_buf[101];
//ѭ����������
	puts("\n================��ʼ׼�������ļ�����==============\n\n");
	while (feof(fsource) == 0)
	{
		//Sleep(5);
		fgets(Send_File_buf, 100, fsource);
		send(socket_Client, Send_File_buf, strlen(Send_File_buf) + 1, 0);
	}
		puts("==================�����ļ��������================\n\n");
//�ر��ļ�����
	Condition = fclose(fsource);
	if (Condition == EOF)
	{
		puts("�����ļ��ر�ʧ�ܣ���������˳�");
		closesocket(socket_Server);
		WSACleanup();
		getchar();
		exit(-1);
	}
	closesocket(socket_Client);
	WSACleanup();
	puts("==============�����������������˳�==============\n\n");
	getchar();
}
