// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPaddleController.h"
#include "GameFramework/PawnMovementComponent.h"

void APlayerPaddleController::Possess(APawn* plyr)
{
	ControllingPlayer = Cast<APlayerPaddle>(plyr);
	this->SetViewTarget(plyr);
	this->AttachToPawn(plyr);
}

void APlayerPaddleController::SetupInputComponent()
{
	Super::SetupInputComponent();

}