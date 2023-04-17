#include "ServerActor.h"
#include "HttpModule.h"


AServerActor::AServerActor()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AServerActor::BeginPlay()
{
	Super::BeginPlay();
	
	SendHttpRequest();

}

void AServerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AServerActor::SendHttpRequest()
{
	HttpRequest = FHttpModule::Get().CreateRequest();	//http 모듈의 인스턴스를 가져와 생성
	HttpRequest->SetVerb("GET");	//요청 메서드를 설정
	HttpRequest->SetURL("http://example.com");	//요청을 보낼 URL 설정
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &AServerActor::OnHttpResponseReceived);	//응답을 처리할 콜백함수, 응답이 되면 함수실행
	HttpRequest->ProcessRequest();	//요청보내기
}

void AServerActor::OnHttpResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
{
	if (bSuccess && Response.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Http 통신이 되었습니다."));
	}
}


