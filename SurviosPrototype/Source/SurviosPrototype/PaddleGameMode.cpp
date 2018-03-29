// Fill out your copyright notice in the Description page of Project Settings.

#include "PaddleGameMode.h"
#include "PlayerPController.h"
#include "UObject/ConstructorHelpers.h"
#include "ScoreHandler.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/LocalPlayer.h"

APaddleGameMode::APaddleGameMode()
{
	UScoreHandler::CreateScores();

	ConstructorHelpers::FClassFinder<APlayerPaddle> player(TEXT("/Game/Blueprints/Player"));
	
	if (player.Succeeded())
		PlayerClass = player.Class;
	else
		PlayerClass = APlayerPaddle::StaticClass();

	PlayerControllerClass = APlayerPController::StaticClass();
}

void APaddleGameMode::BeginPlay()
{
	Super::BeginPlay();
}