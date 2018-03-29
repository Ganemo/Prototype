// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaddleGameMode.h"
#include "PaddleGameMode_TwoPlayer.generated.h"

/**
 * 
 */
UCLASS()
class SURVIOSPROTOTYPE_API APaddleGameMode_TwoPlayer : public APaddleGameMode
{
	GENERATED_BODY()
	
	
public:
	void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable, Category = GameMode)
	virtual void SpawnBall();

};
