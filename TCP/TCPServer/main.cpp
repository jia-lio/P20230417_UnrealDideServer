#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS


//---C
#include <WinSock2.h>
//---C++
#include <iostream>
#include <mysql.h>
//---Plugin Library
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "libmysql.lib")

using namespace std;

#pragma pack(push, 1)
struct MyData
{
	int PlayerNum;
	uint16_t ServerPort;
	char IP[16];
};
#pragma pack(pop)

int main()
{
	//---MySQL
	MYSQL mysql;
	mysql_init(&mysql);
	if(!mysql_real_connect(&mysql, "192.168.0.15:3306", "sihoon", "qwer1234",)


	//---WinSock
	//WSAData wsaData;

	int Result = WSAStartup(MAKEWORD(2, 2), &wsaData);		//winsock 초기화
	if (Result != 0) { cout << "WinSock2 Error"; return -1; }	//초기화 안되면 에러처리

	SOCKET TCPServerSocket = socket(PF_INET, SOCK_STREAM, 0);	//가상의 socket 만들기
	if (TCPServerSocket == INVALID_SOCKET) { cout << "Can't make Socket" << GetLastError(); return -1; }

	SOCKADDR_IN TCPServerSocketAddr;	//소켓 주소 구조체 만들기
	memset(&TCPServerSocketAddr, NULL, sizeof(TCPServerSocketAddr));	//초기화
	TCPServerSocketAddr.sin_family = AF_INET;				//IPv4
	TCPServerSocketAddr.sin_port = htons(10000);			//port
	TCPServerSocketAddr.sin_addr.s_addr = INADDR_ANY;		//모두 수신

	//socket 연결
	Result = bind(TCPServerSocket, (SOCKADDR*)&TCPServerSocketAddr, sizeof(TCPServerSocketAddr));
	if (Result == SOCKET_ERROR) { cout << "Can't bind" << GetLastError(); return -1; }

	//server 열기
	Result = listen(TCPServerSocket, 0);
	if (Result == SOCKET_ERROR) { cout << "Can't listen" << GetLastError(); return -1; }

	//fd  
	fd_set ReadSockets;
	fd_set CopyReadSockets;
	FD_ZERO(&ReadSockets);
	FD_SET(TCPServerSocket, &ReadSockets);

	//반복
	TIMEVAL TimeOut;
	TimeOut.tv_sec = 0;
	TimeOut.tv_usec = 100;

	//무한루프
	while (1)
	{
		CopyReadSockets = ReadSockets;			//복제
		int ChangeCount = select(0, &CopyReadSockets, 0, 0, &TimeOut);	//수신 가능한 데이터가 있는 소켓 갯수
		if (ChangeCount == 0) continue;	//수신이 가능한 소켓이 없다, 다시돌려
		else
		{
			for (int i = 0; i < (int)ReadSockets.fd_count; ++i)
			{
				if (FD_ISSET(ReadSockets.fd_array[i], &CopyReadSockets))
				{
					if (ReadSockets.fd_array[i] == TCPServerSocket)
					{
						SOCKADDR_IN DediServerSockAddr;
						memset(&DediServerSockAddr, NULL, sizeof(DediServerSockAddr));
						int DediServerSockAddrLength = sizeof(DediServerSockAddr);

						SOCKET DediServerSocket = accept(TCPServerSocket, (SOCKADDR*)&DediServerSockAddr, &DediServerSockAddrLength);
						FD_SET(DediServerSocket, &ReadSockets);
					}
					else
					{
						char Buffer[1024] = { 0, };
						int RecvBytes = recv(ReadSockets.fd_array[i], Buffer, sizeof(int), 0);
						Buffer[RecvBytes] = '\0';	//버퍼의 마지막에 null추가
						if (RecvBytes == 0)	//데이터를 수신하지 않음
						{
							closesocket(ReadSockets.fd_array[i]);
							FD_CLR(ReadSockets.fd_array[i], &ReadSockets);
						}
						else if (RecvBytes < 0)	//에러 
						{
							cout << "Error : " << GetLastError();
							closesocket(ReadSockets.fd_array[i]);
							FD_CLR(ReadSockets.fd_array[i], &ReadSockets);
						}
						else
						{
							int number;
							memcpy(&number, Buffer, sizeof(int));
							//20230426 받은 데이터 : 서버
							if (number == 1)
							{
								char DediServerBuffer[1024] = { 0, };  
								int DediServerRecvBytes = recv(ReadSockets.fd_array[i], DediServerBuffer, sizeof(DediServerBuffer), 0);
								DediServerBuffer[DediServerRecvBytes] = '\0';	//버퍼의 마지막에 null추가
								MyData data;
								memcpy(&data, DediServerBuffer, sizeof(MyData));
								cout << "----------DediServer----------" << endl;
								cout << "PlayerNum : " << data.PlayerNum << endl;
								cout << "ServerPort : " << data.ServerPort << endl;
								cout << "IP : " << data.IP << endl;

								//20230426 DB연결
								


							}
							//20230426 받은 데이터 : 클라
							else
							{
								//1. db에서 포트번호랑 ip 받기
								//2. 받은 정보를 클라에 넘겨주기
								cout << "----------ClientServer----------" << endl;
								cout << "Client!" << endl;
							}
						}
					}
				}
			}
		}
	}

	closesocket(TCPServerSocket);		//소켓삭제
	WSACleanup();	//해제

	return 0;
}