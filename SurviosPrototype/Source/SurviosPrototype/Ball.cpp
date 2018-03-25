// Fill out your copyright notice in the Description page of Project Settings.

#include "Ball.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "CanInteractWithBall.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Ball = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball"));
	RootComponent = Ball;
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetupAttachment(Ball);


	ConstructorHelpers::FObjectFinder<UStaticMesh> msh(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (msh.Succeeded())
		Ball->SetStaticMesh(msh.Object);

	Ball->SetWorldScale3D(FVector(.5, .5, .5));

	Ball->SetSimulatePhysics(true);
	Ball->BodyInstance.bLockXRotation = true;
	Ball->BodyInstance.bLockYRotation = true;
	Ball->BodyInstance.bLockZRotation = true;
	Ball->SetMassOverrideInKg(NAME_None, 1, true);
	Ball->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
	//Ball->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Ball->SetNotifyRigidBodyCollision(true);
	Ball->OnComponentHit.AddDynamic(this, &ABall::OnHit);

	Collision->SetSphereRadius(40);
	Collision->SetVisibility(true);
	Collision->SetHiddenInGame(false);

	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collision->SetCollisionProfileName("OverlapAll");
	Collision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ABall::OnOverlap);
	Collision->OnComponentEndOverlap.AddDynamic(this, &ABall::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABall::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (UKismetSystemLibrary::DoesImplementInterface(OtherActor, UCanInteractWithBall::StaticClass()))
	{
		ICanInteractWithBall::Execute_ContactWithBall_Begin(OtherActor, this);
		ICanInteractWithBall::Execute_ContactWithBall_End(OtherActor, this);
	}
	else
	{
		Ball->SetPhysicsLinearVelocity(GetVelocity().GetSafeNormal() * 2000);
	}
		
}

void ABall::OnOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (UKismetSystemLibrary::DoesImplementInterface(OtherActor, UCanInteractWithBall::StaticClass()))
	{
		ICanInteractWithBall::Execute_ContactWithBall_Begin(OtherActor, this);
	}
}
void ABall::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (UKismetSystemLibrary::DoesImplementInterface(OtherActor, UCanInteractWithBall::StaticClass()))
	{
		ICanInteractWithBall::Execute_ContactWithBall_End(OtherActor, this);
	}
}

void ABall::SendBall(FVector destination)
{
	FVector tossvel;
	UGameplayStatics::SuggestProjectileVelocity(this, tossvel, GetActorLocation(), destination, 2000, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace);
	Ball->SetPhysicsLinearVelocity(tossvel);
}

void ABall::LaunchBall(FVector direction, float strength)
{
	direction.Normalize();

	FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
	RV_TraceParams.bTraceComplex = false;
	RV_TraceParams.bTraceAsyncScene = true;
	RV_TraceParams.bReturnPhysicalMaterial = false;

	//Re-initialize hit info
	FHitResult RV_Hit(ForceInit);

	//call GetWorld() from within an actor extending class
	GetWorld()->LineTraceSingleByChannel(
		RV_Hit,        //result
		GetActorLocation(),    //start
		GetActorLocation() + (direction * 6000), //end
		ECC_Visibility, //collision channel
		RV_TraceParams
	);

	
	FVector tossvel;

	if (RV_Hit.bBlockingHit && RV_Hit.Location.Z > 2 && RV_Hit.Location.X >= 250)
	{
		if (RV_Hit.Location.Z < 50)
			RV_Hit.Location.Z = 50;

		UGameplayStatics::SuggestProjectileVelocity(this, tossvel, GetActorLocation(), RV_Hit.Location, 2000, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace, FCollisionResponseParams::DefaultResponseParam, TArray<AActor*>(), true);
	}
	else if (direction.X != 0 && direction.Y != 0)
	{
		FVector destination(0,0,0);
		FMath::SegmentIntersection2D(GetActorLocation(), GetActorLocation() + (direction * 6000), FVector(250, -500, 0), FVector(250, 500, 0), destination);
		destination.Z = 100;

		if (destination.Y > 450)
			destination.Y = 450;
		else if (destination.Y < -450)
			destination.Y = -450;

		UGameplayStatics::SuggestProjectileVelocity(this, tossvel, GetActorLocation(), destination, 2000, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace);
	}
	else
	{
		Deflect(FVector(0, 0, 1));
		return;
	}

	Ball->SetPhysicsLinearVelocity(tossvel);
}

void ABall::Deflect(FVector Normal)
{
	FVector Velocity = GetVelocity().GetSafeNormal() * 100;

	Normal.Normalize();

	FVector u = (FVector::DotProduct(Velocity, Normal)) * Normal;
	FVector w = Velocity - u;
	
	FVector NewVelocity = (friction * w) - (elasticity * u);

	UE_LOG(LogTemp, Log, TEXT("Setting Velocity After Deflect: %s"), *NewVelocity.ToString());

	Ball->SetPhysicsLinearVelocity(NewVelocity);
	//Ball->AddImpulse(NewVelocity);
}
