// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Ball.generated.h"

UCLASS()
class SURVIOSPROTOTYPE_API ABall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABall();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void OnOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UStaticMeshComponent* Ball;
	USphereComponent* Collision;

	FVector OldVel;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float friction = 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float elasticity = 1;

	UPROPERTY(BlueprintReadWrite)
	bool bHitWall = false;

	UFUNCTION(BlueprintCallable, Category = "BallInteraction")
	void SendBall(FVector destination);

	UFUNCTION(BlueprintCallable, Category = "BallInteraction")
	void LaunchBall(FVector direction, float strength = 1);

	UFUNCTION(BlueprintCallable, Category = "BallInteraction")
	void Deflect(FVector Normal);
};
