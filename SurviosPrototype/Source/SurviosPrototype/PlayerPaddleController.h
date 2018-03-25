// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerPaddle.h"
#include "PlayerPaddleController.generated.h"

/**
 * 
 */
UCLASS()
class SURVIOSPROTOTYPE_API APlayerPaddleController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void Possess(APawn* plyr) override;
	void SetupInputComponent() override;

private:
	APlayerPaddle* ControllingPlayer;

};
