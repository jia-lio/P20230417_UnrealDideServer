// Fill out your copyright notice in the Description page of Project Settings.


#include "TestPlayerController.h"

void ATestPlayerController::BeginPlay()
{
	FString ServerAddress = "127.0.0.1:7777";	//주소
	this->ClientTravel(ServerAddress, TRAVEL_Absolute);	//클라가 서버에 입장
}
