// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/AudioComponent.h"
#include "Ball.generated.h"

UCLASS()
class SURVIOSPROTOTYPE_API ABall : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	UStaticMeshComponent* Ball;

	UPROPERTY(BlueprintReadWrite)
	USphereComponent* Collision;

	UPROPERTY(BlueprintReadWrite)
	UAudioComponent* Sound;

	UPROPERTY(BlueprintReadWrite)
	FVector CurrentDestination;

	UPROPERTY(BlueprintReadWrite)
	bool bIsOut = false;

	UPROPERTY(BlueprintReadWrite)
	bool bHitWall = false;

	UPROPERTY(BlueprintReadWrite)
	float launchvelocity = 1500;

	UPROPERTY(BlueprintReadOnly)
	int LastPlayerHit;
	
public:	
	// Sets default values for this actor's properties
	ABall();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "BallInteraction")
	void SetLastPlayerHit(int player);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void OnOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable, Category = "BallInteraction")
	void SendBall(FVector destination);
	UFUNCTION(BlueprintCallable, Category = "BallInteraction")
	void Deflect(FVector Normal);

	UFUNCTION(BlueprintCallable, Category = "BallInteraction")
	virtual void LaunchBall(FVector direction) {};

};