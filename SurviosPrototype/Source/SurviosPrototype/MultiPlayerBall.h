// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ball.h"
#include "MultiPlayerBall.generated.h"

/**
 * 
 */
UCLASS()
class SURVIOSPROTOTYPE_API AMultiPlayerBall : public ABall
{
	GENERATED_BODY()
	
public:
	void LaunchBall(FVector direction) override;
	
};
