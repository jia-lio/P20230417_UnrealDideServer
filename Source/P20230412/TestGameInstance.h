#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TestGameInstance.generated.h"

UCLASS()
class P20230412_API UTestGameInstance : public UGameInstance
{
	GENERATED_BODY()


public:
	UTestGameInstance() { };
	virtual void Init() override;

};
