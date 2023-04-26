#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/EditableText.h"
#include "Json.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

#include "TestLoginWidget.generated.h"

UCLASS()
class P20230412_API UTestLoginWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	class UEditabletext* ID;
	class UEditabletext* Pass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString ID_UMG;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Pass_UMG;

	UFUNCTION(BlueprintCallable)
	void OnLoginButtonClicked();

	UFUNCTION(BlueprintCallable)
	void TestPass();

};
