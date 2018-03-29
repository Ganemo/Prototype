// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerPaddle.h"
#include "PlayerPController.generated.h"

/**
 * 
 */
UCLASS()
class SURVIOSPROTOTYPE_API APlayerPController : public APlayerController
{
	GENERATED_BODY()
	
public:
	APlayerPController();
	void BeginPlay() override;
	void Possess(APawn* pawn) override;

	void MovePawnToLocation(FVector loc);
	void SetPawnLefty(bool bLefty);
	
private:
	APlayerPaddle* ControlledPlayer;
	TSubclassOf<APlayerPaddle> PlayerClass;
};
