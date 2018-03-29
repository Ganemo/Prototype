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

	UPROPERTY(BlueprintReadOnly)
	int PlayerIndex;

	UPROPERTY(BlueprintReadWrite)
	float Rotation = 0;

	UPROPERTY(BlueprintReadWrite)
	bool bIsLefty = true;

	UPROPERTY(BlueprintReadWrite)
	bool bCanSwing = true;

	UPROPERTY(BlueprintReadWrite)
	bool bActiveSwing = false;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	bool bIsPlayerRotating = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveRight(float Axis);
	void Rotate(float Direction);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = PlayerActions)
	void Init();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = PlayerActions)
	void Swing();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = PlayerActions)
	void SetPaddleState(bool NewState);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = PlayerActions)
	void StrikeBall(class ABall* Ball);
};
