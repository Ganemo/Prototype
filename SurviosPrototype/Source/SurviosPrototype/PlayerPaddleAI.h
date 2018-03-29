// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerPaddle.h"
#include "PlayerPaddleAI.generated.h"

/**
 * 
 */
UCLASS()
class SURVIOSPROTOTYPE_API APlayerPaddleAI : public APlayerPaddle
{
	GENERATED_BODY()

public:
	void Tick(float DeltaTime) override;
	
};
