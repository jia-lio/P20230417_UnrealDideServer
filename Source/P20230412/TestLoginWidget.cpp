#include "TestLoginWidget.h"
#include "Kismet/GameplayStatics.h"
#include "LoginGameMode.h"


void UTestLoginWidget::OnLoginButtonClicked()
{
    ////������ �����ϰ��ϴ� �� 
    //ALoginGameMode* gamemode = Cast<ALoginGameMode>(GetWorld()->GetAuthGameMode());
    //if (gamemode != NULL) gamemode->ClientTCPInfo();

    //�䳪�߿� ������ �Ǹ� �ּ�����!
    // EditableText ���� FString�� ����
    // Id & Password = FID & FPassword
    if (Id && Id->HasKeyboardFocus())
    {
        FID = Id->GetText().ToString();
    }
    else if (Password && Password->HasKeyboardFocus())
    {
        FPassword = Password->GetText().ToString();
    }

    // JSON ������ ����
    //TSharedPtr<FJsonObject>�� JSON ������ Ŭ���� ����Ʈ������ ����
    //JsonObject�� ����Ʈ�����͸� ����Ű�� ������
    //MakeShareable()�� ���ڷ� ���� ��ü�� ����Ʈ �����Ͱ� �����ϵ��� ������ִ� �Լ�
    //SetStringField(TEXT("email"), FID)�� email ���ڿ� �ʵ忡 FID���� ����
    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
    JsonObject->SetStringField(TEXT("email"), FID);
    JsonObject->SetStringField(TEXT("password"), FPassword);

    // JSON �����͸� ���ڿ��� ��ȯ
    //JSON �����͸� ���ڿ��� �����ϱ� ���� ����
    //TJsonWriterFactory�� TJsonWriter<TCHAR> Ŭ������ �ν��Ͻ� ���� &JsonString�� ���ڷ� �����Ͽ� JsonString�� JSON �����͸� ���� �� ���
    //FJsonSerializer�� ����Ͽ� JsonObject�� JsonWriter�� ���� ���ڿ��� ����ȭ
    //Serialize() �Լ��� JsonWriter�� ���� JSON ���ڿ��� �����ϰ�, JsonString�� ����
    FString JsonString;
    TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&JsonString);
    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);

    // HTTP ��û ���� �� ����
    //CreateRequest �Լ��� ȣ���Ͽ� HTTP ��û ��ü ����, �ش� ��ü�� ���� TSharedRef ����Ʈ ������ ����
    //HTTP ��û ��ü�� �޼ҵ带 POST�� ����
    //HTTP ��û�� ���� ��� �� Content-Type ����� application/json �� ����
    //HTTP ��û URL�� �ش� URL�� ����
    //HTTP ��û�� body�� JSON ���ڿ��� JsonString ����
    TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();//��û ����
    HttpRequest->SetVerb(TEXT("POST"));//��û�� �������
    HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));//��û�� �������
    HttpRequest->SetURL(TEXT("http://192.168.0.10:8080/login"));//��û�� �������
    HttpRequest->SetContentAsString(JsonString);//��û�� �������

    // ��û �Ϸ� �� HandleHttpRequestComplete �Լ� ȣ���Ͽ� ��� ó��
    HttpRequest->OnProcessRequestComplete().BindUObject(this, &UTestLoginWidget::HandleHttpRequestComplete);

    // ������ HTTP ��û�� ������ ����
    //�� �޼ҵ尡 ȣ����� ������ ������ ���� �ȵ�
    HttpRequest->ProcessRequest();

   
}

void UTestLoginWidget::OnCreateSignUpButtonClicked()
{
  
}

void UTestLoginWidget::OnSignUpButtonClicked()
{
    // Id�� Password �Է°� ����
    if (Id && Id->HasKeyboardFocus())
    {
        FID = Id->GetText().ToString();
    }
    else if (Password && Password->HasKeyboardFocus())
    {
        FPassword = Password->GetText().ToString();
    }

    // JSON ������ ����
    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
    JsonObject->SetStringField(TEXT("email"), FID);
    JsonObject->SetStringField(TEXT("password"), FPassword);

    // JSON �����͸� ���ڿ��� ��ȯ
    FString JsonString;
    TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&JsonString);
    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);

    // HTTP ��û ���� �� ����
    TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->SetVerb(TEXT("POST"));
    HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
    HttpRequest->SetURL(TEXT("http://192.168.0.10:8080/signup"));
    HttpRequest->SetContentAsString(JsonString);

    // ��û �Ϸ� �� ȣ���� �Լ� ����
    HttpRequest->OnProcessRequestComplete().BindUObject(this, &UTestLoginWidget::HandleHttpRequestComplete);

    // ��û ����
    HttpRequest->ProcessRequest();

}

void UTestLoginWidget::OnBackButtonClicked()
{

}


void UTestLoginWidget::NativeConstruct()
{
    UButton* LoginButton = Cast<UButton>(GetWidgetFromName(TEXT("Login")));
    UButton* SignUpButton = Cast<UButton>(GetWidgetFromName(TEXT("signup")));
    // ��ư �̺�Ʈ �ڵ鷯 ����ϱ�
    if (LoginButton)
    {
        LoginButton->OnClicked.AddDynamic(this, &UTestLoginWidget::OnLoginButtonClicked);
        UE_LOG(LogTemp, Warning, TEXT("�α��� ��ư �̺�Ʈ��!!"));
    }
    if (SignUpButton)
    {
        SignUpButton->OnClicked.AddDynamic(this, &UTestLoginWidget::OnCreateSignUpButtonClicked);
        UE_LOG(LogTemp, Warning, TEXT("ȸ������â���� �Ѿ�� ��ư �̺�Ʈ��!!"));

    }

    UButton* CreateSignUpButton = Cast<UButton>(GetWidgetFromName(TEXT("CreateSignUpButton")));

    UButton* BackButton = Cast<UButton>(GetWidgetFromName(TEXT("BackButton")));
    // ��ư �̺�Ʈ �ڵ鷯 ����ϱ�
    if (CreateSignUpButton)
    {
        CreateSignUpButton->OnClicked.AddDynamic(this, &UTestLoginWidget::OnSignUpButtonClicked);
    }
    if (BackButton)
    {
        BackButton->OnClicked.AddDynamic(this, &UTestLoginWidget::OnBackButtonClicked);
    }
}

void UTestLoginWidget::HandleHttpRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
{
    if (bSuccess && Response.IsValid())
    {
        UE_LOG(LogTemp, Warning, TEXT("Response: %s"), *Response->GetContentAsString());

        // Convert response json to object
        TSharedPtr<FJsonObject> JsonObject;
        TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(Response->GetContentAsString());

        //login gamemode : tcp �Լ��� ����
        ALoginGameMode* gamemode = Cast<ALoginGameMode>(GetWorld()->GetAuthGameMode());
        if (gamemode != NULL) gamemode->ClientTCPInfo();
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Http request failed"));
    }
}

