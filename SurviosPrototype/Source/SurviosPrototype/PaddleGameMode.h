// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PaddleGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SURVIOSPROTOTYPE_API APaddleGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	APaddleGameMode();

	void BeginPlay() override;
	
};
