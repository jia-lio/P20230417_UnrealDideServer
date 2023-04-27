#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/EditableText.h"
#include "Components/Button.h"
#include "UObject/ConstructorHelpers.h"
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
    UPROPERTY(BlueprintReadWrite)
        UEditableText* Id;

    UPROPERTY(BlueprintReadWrite)
        UEditableText* Password;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FString FID;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FString FPassword;

    UFUNCTION(BlueprintCallable)
        void OnLoginButtonClicked();

    UFUNCTION(BlueprintCallable)
        void OnCreateSignUpButtonClicked();

    UFUNCTION(BlueprintCallable)
        void OnSignUpButtonClicked();

    UFUNCTION(BlueprintCallable)
        void OnBackButtonClicked();



    void NativeConstruct(); //widget beginplay
    //wepserver 요청보내주기
    void HandleHttpRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess);






};
