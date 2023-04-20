#include "USingleton.h"

UUSingleton* UUSingleton::GetInstance()
{
    if (instance == NULL)
    {
        instance = NewObject<UUSingleton>();
    }
    return instance;
}

void UUSingleton::SetData(int playernum, int serverport, FString ip)
{
    data.PlayerNum = playernum;
    data.ServerPort = serverport;
    data.IP = ip;
}












