#include "TestGameInstance.h"

void UTestGameInstance::Init()
{
    Super::Init();

    //삽질의 흔적
    //if (GetWorld()->IsServer() && GEngine)
    //{
    //    UE_LOG(LogTemp, Warning, TEXT("Server instance"));
    //}
    //else
    //{
    //    UE_LOG(LogTemp, Warning, TEXT("Client instance"));
    //}
}