#include<winsock2.h>
#include<stdio.h>
#pragma comment(lib, "ws2_32.lib")
#define PORT 6013
#define IP "172.30.58.113"
int main(void)
{
	Sleep(1000);
	int Condition;
//����Ŀ���ļ�������
	FILE *ftarget;
	ftarget = fopen("C:\\Users\\Administrator\\Desktop\\The Little Prince_COPY.txt", "w");
	if (ftarget == NULL)
	{
		puts("�����ļ�����ʧ��,��������˳�");
		getchar();
		exit(-1);
	}
	puts("=============�ļ������ɹ�==================\n\n");
//�����׽���
	WSADATA wsaData;
	SOCKADDR_IN addrServer;
	SOCKET socket_Client;
	Condition = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (Condition != 0)
	{
		puts("����Windows Socket API ����ʧ�ܣ���������˳�");
		getchar();
		exit(-1);
	}
	socket_Client = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_Client == INVALID_SOCKET)
	{
		puts("����SOCKET ����ʧ�ܣ���������˳�");
		WSACleanup();
		getchar();
		exit(-1);
	}
	addrServer.sin_addr.S_un.S_addr = inet_addr(IP);
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(PORT);
//���ӵ�������
	Condition = connect(socket_Client, (SOCKADDR*)&addrServer, sizeof(SOCKADDR));
	if (Condition == SOCKET_ERROR)
	{
		puts("�������ӵ�������ʧ�ܣ���������˳�");
		WSACleanup();
		getchar();
		exit(-1);
	}
	puts("=============�ɹ����ӵ�������==============\n\n");
	char send_massage[100] = "���Կͻ��ˣ��ͻ����Ѿ�����";
	char recvBuf[100];
	send(socket_Client, send_massage, strlen(send_massage) + 1, 0);
	Condition = recv(socket_Client, recvBuf, 100, 0);
	if (Condition == SOCKET_ERROR)
	{
		puts("���󣺽�������ʧ�ܣ���������˳�");
		WSACleanup();
		getchar();
		exit(-1);
	}
	printf("%s\n", recvBuf);
	char Recv_File_buf[101];
	puts("\n=============׼�������ļ�����==============\n\n");
//ѭ�����գ���д������
	while (Condition != 0)
	{
		Condition = recv(socket_Client, Recv_File_buf, 1000, 0);
		fputs(Recv_File_buf, ftarget);
		//printf("%s", Recv_File_buf);
	
	}
	puts("\n=================�����ļ��������===============\n\n");
//�ر��ļ�����
	Condition = fclose(ftarget);
	if (Condition == EOF)
	{
		puts("�����ļ��ر�ʧ�ܣ���������˳�");
		closesocket(socket_Client);
		WSACleanup();
		getchar();
		exit(-1);
	}
	closesocket(socket_Client);
	WSACleanup();
	puts("=============�����������������˳�=============\n\n");
	getchar();
}