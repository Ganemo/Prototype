// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CanInteractWithBall.h"
#include "PlayerPaddle.generated.h"

UCLASS()
class SURVIOSPROTOTYPE_API APlayerPaddle : public ACharacter, public ICanInteractWithBall
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPaddle();

	UPROPERTY(BlueprintReadWrite)
	float Rotation = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveRight(float axis);
	void Rotate(float direction);

	UFUNCTION(BlueprintImplementableEvent, Category = PlayerActions)
	void Swing();

};
