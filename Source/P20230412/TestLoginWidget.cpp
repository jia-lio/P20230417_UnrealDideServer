#include "TestLoginWidget.h"
#include "Kismet/GameplayStatics.h"

void UTestLoginWidget::OnLoginButtonClicked()
{
	//20230426 �ӽ� ���� ����
	FString ServerAddress = "127.0.0.1:7777";	//�ּ�
	//this->ClientTravel(ServerAddress, TRAVEL_Absolute);	//Ŭ�� ������ ����
	GetWorld()->GetFirstPlayerController()->ClientTravel(ServerAddress, TRAVEL_Absolute);

}

void UTestLoginWidget::TestPass()
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Pass_UMG);
}
