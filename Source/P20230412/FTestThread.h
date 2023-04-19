#pragma once

#include "CoreMinimal.h"

class P20230412_API FTestThread : public FRunnable
{
public:
	FTestThread();
	FTestThread(const FString& m);
	~FTestThread();

	bool Init() override;
	virtual uint32 Run() override;	//데이터를 보내는
	virtual void Stop() override;	//스레드 중지


private:
	FString Message;
	TSharedPtr<FInternetAddr> DediServerAddress;
	class FSocket* DediServerSocket;
	class FRunnableThread* thread;

	bool bRunThread = false;
};
 