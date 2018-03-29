// Fill out your copyright notice in the Description page of Project Settings.

#include "PaddleGameMode_SinglePlayer.h"
#include "PlayerPController.h"
#include "UObject/ConstructorHelpers.h"
#include "ScoreHandler.h"
#include "Kismet/GameplayStatics.h"
#include "SinglePlayerBall.h"



void APaddleGameMode_SinglePlayer::BeginPlay()
{
	Super::BeginPlay();

	APlayerPController* cont1 = Cast<APlayerPController>(UGameplayStatics::GetPlayerController(this, 0));
	APlayerPaddle* pad1 = GetWorld()->SpawnActor<APlayerPaddle>(PlayerClass, FVector(250, -90, 102), FRotator(0, 0, 0));
	pad1->bIsLefty = true;
	pad1->Init();
	cont1->Possess(pad1);
}

void APaddleGameMode_SinglePlayer::SpawnBall()
{
	if (BallCount <= 0)
	{
		APlayerPaddle* plyr = Cast<APlayerPaddle>(UGameplayStatics::GetPlayerCharacter(this, 0));
		if (plyr != nullptr)
		{
			GetWorld()->SpawnActor<ASinglePlayerBall>(ASinglePlayerBall::StaticClass(), plyr->GetActorLocation() + FVector(0, plyr->bIsLefty ? 100 : -100, 50), FRotator(0, 0, 0));
			BallCount++;
		}
	}
}