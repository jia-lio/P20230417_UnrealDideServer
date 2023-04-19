// Copyright Epic Games, Inc. All Rights Reserved.

#include "P20230412GameMode.h"
#include "P20230412Character.h"
#include "TestPlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "FTestThread.h"

#include <string>

AP20230412GameMode::AP20230412GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	
	
}



void AP20230412GameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	//if (NewPlayer->HasClientLoadedCurrentWorld())
	//{
	//	NewPlayer->AcknowledgePossession(NewPlayer->GetPawn());
	//	NewPlayer->ClientMessage(FString::Printf(TEXT("어서와 데디서버에")));
	//	UE_LOG(LogTemp, Warning, TEXT("클라이언트가 드루왓다"));
	//}

	UE_LOG(LogTemp, Warning, TEXT("클라이언트가 드루왓다"));

	FTestThread* Sender = new FTestThread(FString::Printf(TEXT("%i"), GetNumPlayers()));
	//FTestThread* Sender = new FTestThread(TEXT("d"));
	FRunnableThread* Thread = FRunnableThread::Create(Sender, TEXT("SendThread"));
}
