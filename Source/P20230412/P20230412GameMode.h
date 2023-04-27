// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "P20230412GameMode.generated.h"

UCLASS(minimalapi)
class AP20230412GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AP20230412GameMode();
	
	virtual void InitGameState() override;

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
	 
	void InforThread();

};



