#include "TestLoginWidget.h"
#include "Kismet/GameplayStatics.h"

void UTestLoginWidget::OnLoginButtonClicked()
{
	//20230426 임시 데디 입장
	FString ServerAddress = "127.0.0.1:7777";	//주소
	//this->ClientTravel(ServerAddress, TRAVEL_Absolute);	//클라가 서버에 입장
	GetWorld()->GetFirstPlayerController()->ClientTravel(ServerAddress, TRAVEL_Absolute);

}

void UTestLoginWidget::TestPass()
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Pass_UMG);
}
