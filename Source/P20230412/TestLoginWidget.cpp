#include "TestLoginWidget.h"

void UTestLoginWidget::TestID()
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *ID_UMG);
}

void UTestLoginWidget::TestPass()
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Pass_UMG);
}
