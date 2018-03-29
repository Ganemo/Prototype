// Fill out your copyright notice in the Description page of Project Settings.

#include "SinglePlayerBall.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "CanInteractWithBall.h"

const FName TraceTag("BallLaunchTrace");

void ASinglePlayerBall::LaunchBall(FVector direction)
{
	if (!bIsOut)
	{
		if (direction.Z < 0)
			direction.Z = 0;

		if (bHitWall)
		{
			direction.X = -1 * FMath::Abs(direction.X);
		}
		else
		{
			direction.X = FMath::Abs(direction.X);
		}

		direction.Normalize();

		FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
		RV_TraceParams.bTraceComplex = false;
		RV_TraceParams.bTraceAsyncScene = true;
		RV_TraceParams.bReturnPhysicalMaterial = false;
		RV_TraceParams.TraceTag = TraceTag;

		//Re-initialize hit info
		FHitResult RV_Hit(ForceInit);

		GetWorld()->DebugDrawTraceTag = TraceTag;

		//call GetWorld() from within an actor extending class
		GetWorld()->LineTraceSingleByChannel(
			RV_Hit,        //result
			GetActorLocation(),    //start
			GetActorLocation() + (direction * 6000), //end
			ECC_Visibility, //collision channel
			RV_TraceParams
		);

		if (RV_Hit.IsValidBlockingHit())
		{
			FVector HitLoc = RV_Hit.Location;

			if (bHitWall)
			{
				//if the hit location is behind the player
				//put the ball on the player's plane
				if (HitLoc.X < 250)
				{
					HitLoc.X = 250;
					HitLoc.Z = 100;

					HitLoc.Y = FMath::Clamp<int>(HitLoc.Y, -400, 400);
				}
				else
				{
					HitLoc.Z = FMath::Clamp<int>(HitLoc.Z, 200, 500);
				}
			}
			else
			{
				if (HitLoc.X >= 3960)
				{
					HitLoc.X = 3960;
					//HitLoc.Y = FMath::Clamp<int>(HitLoc.Y, -400, 400);
				}
				
				HitLoc.Z = FMath::Clamp<int>(HitLoc.Z, 200, 500);
			}

			UE_LOG(LogTemp, Log, TEXT("HitLocatoin: %s"), *HitLoc.ToString());

			this->SendBall(HitLoc);
		}
	}
}
