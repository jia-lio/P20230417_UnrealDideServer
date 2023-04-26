// Copyright Epic Games, Inc. All Rights Reserved.

#include "P20230412GameMode.h"
#include "P20230412Character.h"
#include "TestPlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "FTestThread.h"
#include "Misc/CommandLine.h"
#include "USingleton.h"
#include "SocketSubsystem.h"
#include "Sockets.h"

#include <string>

AP20230412GameMode::AP20230412GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	//스레드생성
	//FTestThread* Sender = new FTestThread(FString::Printf(TEXT("%i"), GetNumPlayers()));
	FTestThread* Sender = new FTestThread();
	FRunnableThread* Thread = FRunnableThread::Create(Sender, TEXT("SendThread"));
}

void AP20230412GameMode::InitGameState()
{
	InforThread();
}

void AP20230412GameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	UE_LOG(LogTemp, Warning, TEXT("클라이언트가 드루왓다"));

	InforThread();
}

void AP20230412GameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UE_LOG(LogTemp, Warning, TEXT("서버닫는다"));

	Super::EndPlay(EndPlayReason);

	
}

void AP20230412GameMode::InforThread()
{
	//서버의 포트번호 / IP 불러오는 방법
	FString URLString = GetWorld()->URL.ToString();
	FURL URL(NULL, *URLString, ETravelType::TRAVEL_Absolute);
	int32 Port;
	if (URL.Valid && URL.Port > 0)
	{
		Port = URL.Port;
	}

	// Get IP Address
	FString IPAddress = "";
	bool canBind = false;
	TSharedRef<FInternetAddr>LocalIp =
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->GetLocalHostAddr(*GLog, canBind);

	if (LocalIp->IsValid())
	{
		IPAddress = LocalIp->ToString(false);
		UE_LOG(LogTemp, Error, TEXT("GameMode IP : %s"), *IPAddress);
	}

	//싱글톤으로 정보보내기
	//IP 인자값 = 로컬서버를 사용하지 않으면 URL.Host 를 쓰면 된다.
	UE_LOG(LogTemp, Error, TEXT("GameMode Port : %d"), Port);
	UUSingleton::GetInstance()->SetData(GetNumPlayers(), static_cast<int>(Port), *IPAddress);
	UUSingleton::GetInstance()->SerBool(true);
}