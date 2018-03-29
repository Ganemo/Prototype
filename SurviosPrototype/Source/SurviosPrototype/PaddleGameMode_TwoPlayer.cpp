// Fill out your copyright notice in the Description page of Project Settings.

#include "PaddleGameMode_TwoPlayer.h"
#include "PlayerPController.h"
#include "UObject/ConstructorHelpers.h"
#include "ScoreHandler.h"
#include "Kismet/GameplayStatics.h"
#include "MultiPlayerBall.h"



void APaddleGameMode_TwoPlayer::BeginPlay()
{
	Super::BeginPlay();

	APlayerPController* cont1 = Cast<APlayerPController>(UGameplayStatics::GetPlayerController(this, 0));
	APlayerPaddle* pad1 = GetWorld()->SpawnActor<APlayerPaddle>(PlayerClass, FVector(250, -350, 102), FRotator(0, 0, 0));
	pad1->bIsLefty = true;
	pad1->Init();
	cont1->Possess(pad1);


	APlayerPController* cont2 = Cast<APlayerPController>(UGameplayStatics::CreatePlayer(GetWorld(), 1, true));
	APlayerPaddle* pad2 = GetWorld()->SpawnActor<APlayerPaddle>(PlayerClass, FVector(250, 350, 102), FRotator(0, 0, 0));
	pad2->bIsLefty = false;
	pad2->Init();
	cont2->Possess(pad2);
}

void APaddleGameMode_TwoPlayer::SpawnBall()
{
	if (BallCount <= 0)
	{
		APlayerPaddle* plyr = Cast<APlayerPaddle>(UGameplayStatics::GetPlayerCharacter(this, 0));
		if (plyr != nullptr)
		{
			GetWorld()->SpawnActor<AMultiPlayerBall>(AMultiPlayerBall::StaticClass(), plyr->GetActorLocation() + FVector(0, plyr->bIsLefty ? 100 : -100, 50), FRotator(0, 0, 0));
			BallCount++;
		}
	}
}