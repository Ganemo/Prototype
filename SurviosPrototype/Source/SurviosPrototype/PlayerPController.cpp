// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPController.h"
#include "UObject/ConstructorHelpers.h"


APlayerPController::APlayerPController()
{
	ConstructorHelpers::FClassFinder<APlayerPaddle> Player(TEXT("/Game/Blueprints/Player"));
	if (Player.Succeeded())
	{
		PlayerClass = Player.Class;
	}
}

void APlayerPController::BeginPlay()
{
	Super::BeginPlay();

}

void APlayerPController::Possess(APawn* pawn)
{
	Super::Possess(pawn);
	ControlledPlayer = Cast<APlayerPaddle>(pawn);
}

void APlayerPController::MovePawnToLocation(FVector loc)
{
	if (ControlledPlayer != nullptr)
		ControlledPlayer->SetActorLocation(loc);
}

void APlayerPController::SetPawnLefty(bool bLefty)
{
	ControlledPlayer->bIsLefty = bLefty;
}