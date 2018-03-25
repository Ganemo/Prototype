// Fill out your copyright notice in the Description page of Project Settings.

#include "PaddleGameMode.h"
#include "PlayerPaddle.h"
#include "PlayerPaddleController.h"
#include "UObject/ConstructorHelpers.h"


APaddleGameMode::APaddleGameMode()
{
	ConstructorHelpers::FClassFinder<APlayerPaddle> player(TEXT("/Game/Blueprints/Player"));
	
	if (player.Succeeded())
		DefaultPawnClass = player.Class;
	else
		DefaultPawnClass = APlayerPaddle::StaticClass();


	PlayerControllerClass = APlayerPaddleController::StaticClass();
}

void APaddleGameMode::BeginPlay()
{

}