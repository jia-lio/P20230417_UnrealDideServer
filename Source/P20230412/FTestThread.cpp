#include "FTestThread.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "IPAddress.h"

FTestThread::FTestThread()
{

}

FTestThread::FTestThread(const FString& m) : Message(m)
{
	
}

FTestThread::~FTestThread()
{
	//스레드 삭제
	if (thread)
	{
		UE_LOG(LogTemp, Warning, TEXT("스레드 종료."));
		delete thread;
	}
}

bool FTestThread::Init()
{
	bRunThread = true;

	//TCP소켓 생성 연결
	//현재 플렛폼에 맞춰서 소켓을 가져오는 시스템 (새로운 소켓 생성, 소켓 이름, 비차단모드로 설정할지?)
	DediServerSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("DefaultSocket"), false);
	DediServerAddress = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();

	FString IP = TEXT("127.0.0.1");	//tcp ip
	int32 port = 10000;	//tcp port
	FIPv4Address TemporaryAddr;		//임시 저장소
	FIPv4Address::Parse(IP, TemporaryAddr); //ip를 temporaryAddr에 변환해서 넣고
	DediServerAddress->SetPort(port);	//port넣음
	DediServerAddress->SetIp(TemporaryAddr.Value);	//ip넣음

	if (DediServerSocket->Connect(*DediServerAddress))
	{
		UE_LOG(LogTemp, Warning, TEXT("TCP서버에 드루갓다"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TCP서버에 못드루갓다"));
	}

	return true;
}

uint32 FTestThread::Run()
{
	UE_LOG(LogTemp, Warning, TEXT("스레드 보내기."));

	while (bRunThread)
	{
		//소켓과 연결이 끊어지면 종료
		if (DediServerSocket->GetConnectionState() != ESocketConnectionState::SCS_Connected) break;

		//받아온 메세지를 uint8 데이터로 변환
		FString MessageToSend = FString::Printf(TEXT("%s\n"), *Message);
		uint8* Data = (uint8*)TCHAR_TO_UTF8(*MessageToSend);
		int32 BytesSent = 0;

		if (DediServerSocket->GetConnectionState() == ESocketConnectionState::SCS_Connected)
		{
			DediServerSocket->Send(Data, sizeof(Data), BytesSent);	//데이터전송
			bRunThread = false;
		}


		FPlatformProcess::Sleep(0.1f);	//스레드를 잠시 멈춘다
		//정보를 보냈으니 스레드 종료
		if (!bRunThread)
		{
			this->Stop();
			break;
		}
	}

	return 0;
}

void FTestThread::Stop()
{
	bRunThread = false;
	
	UE_LOG(LogTemp, Warning, TEXT("스레드 종료."));
}
