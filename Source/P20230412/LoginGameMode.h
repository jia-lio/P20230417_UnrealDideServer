#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LoginGameMode.generated.h"

UCLASS()
class P20230412_API ALoginGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ALoginGameMode();

	virtual void StartPlay() override;
	virtual void OnPostLogin(AController* NewPlayer) override;
	
	

};
