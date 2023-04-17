#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HttpModule.h"
#include "ServerActor.generated.h"

UCLASS()
class P20230412_API AServerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AServerActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
	//요청을 보내는 함수
	UFUNCTION(BlueprintCallable)
	void SendHttpRequest();

	void OnHttpResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess);

private:
	TSharedPtr<IHttpRequest> HttpRequest;	//IHttpRequest 인터페이스의 스마트포인터

};
