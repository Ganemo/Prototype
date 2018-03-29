// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPaddle.h"
#include "Components/SkeletalMeshComponent.h"
#include "ScoreHandler.h"
#include "Ball.h"


// Sets default values
APlayerPaddle::APlayerPaddle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerPaddle::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerIndex = UScoreHandler::AddPlayer();
}

// Called every frame
void APlayerPaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!bIsPlayerRotating)
		Rotation = FMath::FInterpConstantTo(Rotation, 0, DeltaTime, 20);
}

// Called to bind functionality to input
void APlayerPaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	this->InputComponent->BindAxis("MoveRight", this, &APlayerPaddle::MoveRight);
	this->InputComponent->BindAxis("Rotate", this, &APlayerPaddle::Rotate);
	this->InputComponent->BindAction("Swing", EInputEvent::IE_Pressed, this, &APlayerPaddle::Swing);
}

void APlayerPaddle::MoveRight(float Axis)
{
	if(bCanSwing)
		this->AddMovementInput(this->GetActorRightVector(), Axis * 100);
}

void APlayerPaddle::Rotate(float Direction)
{
	if (Direction == 0)
		bIsPlayerRotating = false;
	else
		bIsPlayerRotating = true;

	if (Rotation + Direction >= -25 && Rotation + Direction <= 25)
	{
		Rotation += Direction;
	}
}

void APlayerPaddle::StrikeBall_Implementation(ABall* Ball)
{
	Ball->bHitWall = false;

	FVector Direction = GetActorForwardVector().RotateAngleAxis(Rotation, FVector(0, 0, 1));
	Ball->LaunchBall(Direction);

	Ball->SetLastPlayerHit(this->PlayerIndex);

	SetPaddleState(false);

	UScoreHandler::AddScore(PlayerIndex, 1);
	Ball->launchvelocity += 50;
}
