#include "LoginGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "TestPlayerController.h"
#include "P20230412Character.h"
#include "TestLoginWidget.h"
#include "IPAddress.h"

//---TCP
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "IPAddress.h"


ALoginGameMode::ALoginGameMode()
{
	PlayerControllerClass = ATestPlayerController::StaticClass();
	DefaultPawnClass = AP20230412Character::StaticClass();

	// UMG_Login 위젯 생성하기
	static ConstructorHelpers::FClassFinder<UTestLoginWidget> LoginWidgetClass(TEXT("/Game/LoginWidget"));
	if (LoginWidgetClass.Succeeded())
	{
		UTestLoginWidget* LoginWidget = CreateWidget<UTestLoginWidget>(GetWorld(), LoginWidgetClass.Class);

		// UMG_Login 위젯 화면에 추가하기
		if (LoginWidget != nullptr)
		{
			LoginWidget->AddToViewport();

			UE_LOG(LogTemp, Warning, TEXT("위젯 뜸"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("위젯 안뜸"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("그냥 다시 해"));
	}
}

void ALoginGameMode::StartPlay()
{
	Super::StartPlay();
	
	


}

void ALoginGameMode::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

	
	
}

void ALoginGameMode::ClientTCPInfo()
{
	ClientSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("DefaultSocket"), false);
	ClientAddress = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();

	FString IP = TEXT("192.168.0.20");	//tcp ip
	int32 port = 10000;	//tcp port
	FIPv4Address TemporaryAddr;		//임시 저장소
	FIPv4Address::Parse(IP, TemporaryAddr); //ip를 temporaryAddr에 변환해서 넣고
	ClientAddress->SetPort(port);	//port넣음
	ClientAddress->SetIp(TemporaryAddr.Value);	//ip넣음

	if (ClientSocket->Connect(*ClientAddress))
	{
		UE_LOG(LogTemp, Warning, TEXT("Client : TCP서버에 드루갓다"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Client : TCP서버에 못드루갓다"));
	}

	int MyClientServer = 2;
	uint8_t buffer[sizeof(int)];
	memcpy(buffer, &MyClientServer, sizeof(int));

	int32 bytesSent = 0;
	if (ClientSocket->GetConnectionState() == ESocketConnectionState::SCS_Connected)
	{
		ClientSocket->Send(buffer, sizeof(int), bytesSent);
	}


	struct ServerData
	{
		uint16_t ServerPort;
		char IP[16];
	};
	ServerData SData;
	uint8_t DBBuffer[1024] = { 0, };
	int32 bytes = 0;
	int ClientServerRecvBytes = 0;

	UE_LOG(LogTemp, Warning, TEXT("TCP DB Data...."));

	if (ClientSocket->Wait(ESocketWaitConditions::WaitForRead, FTimespan::FromSeconds(5)))
	{
		ClientServerRecvBytes = ClientSocket->Recv(DBBuffer, sizeof(DBBuffer), bytes);

		if (ClientServerRecvBytes < 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Error"));
		}
		else if (ClientSocket == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("No Data"));
		}
		else
		{
			//DBBuffer[ClientServerRecvBytes] = '\0';
			UE_LOG(LogTemp, Warning, TEXT("In Data"));
			memcpy(&SData, DBBuffer, sizeof(ServerData));
		
			UE_LOG(LogTemp, Warning, TEXT("%d"), SData.ServerPort);
			FString str(SData.IP);
			str += ":";
			str += FString::FromInt(SData.ServerPort);

			UE_LOG(LogTemp, Warning, TEXT("%s"), *str);

			GetWorld()->GetFirstPlayerController()->ClientTravel(str, TRAVEL_Absolute);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No"));
	}


}

