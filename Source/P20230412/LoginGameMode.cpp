#include "LoginGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "TestPlayerController.h"
#include "P20230412Character.h"

ALoginGameMode::ALoginGameMode()
{
	PlayerControllerClass = ATestPlayerController::StaticClass();
	DefaultPawnClass = AP20230412Character::StaticClass();
}

void ALoginGameMode::StartPlay()
{
	Super::StartPlay();
	
	//FString ServerAddress = "127.0.0.1:7777";
	//APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	//if (PlayerController != nullptr)
	//{
	//	PlayerController->ClientTravel(ServerAddress, TRAVEL_Absolute);
	//	UE_LOG(LogTemp, Warning, TEXT("드루갓다"));
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("이거아니래"));
	//}

	
	//FString ServerAddress = "127.0.0.1:7777"; 
	//UWorld* world = GetWorld();
	//if (world != NULL)
	//{
	//	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	//	if (PlayerController != NULL)
	//	{
	//		PlayerController->ClientTravel(ServerAddress, TRAVEL_Absolute);
	//		UE_LOG(LogTemp, Warning, TEXT("서버에 접속했습니다."));
	//	}
	//	else
	//	{
	//		UE_LOG(LogTemp, Warning, TEXT("PlayerController = null "));
	//	}
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("world = null "));
	//}


}

void ALoginGameMode::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

	/*FString ServerAddress = "127.0.0.1:7777";
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController != nullptr)
	{
		PlayerController->ClientTravel(ServerAddress, TRAVEL_Absolute);
		UE_LOG(LogTemp, Warning, TEXT("드루갓다"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("이거아니래"));
	}*/

}
