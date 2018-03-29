// Fill out your copyright notice in the Description page of Project Settings.

#include "Ball.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Sound/SoundCue.h"
#include "CanInteractWithBall.h"

const FName TraceTag("BallLaunchTrace");

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Ball = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball"));
	RootComponent = Ball;
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetupAttachment(Ball);
	Sound = CreateDefaultSubobject<UAudioComponent>(TEXT("Sound"));
	Sound->SetupAttachment(Ball);


	ConstructorHelpers::FObjectFinder<UStaticMesh> BallMesh(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (BallMesh.Succeeded())
		Ball->SetStaticMesh(BallMesh.Object);

	ConstructorHelpers::FObjectFinder<UMaterialInterface> BallMaterial(TEXT("MaterialInstanceConstant'/Game/Material/BallMat_Inst.BallMat_Inst'"));
	if (BallMaterial.Succeeded())
		Ball->SetMaterial(0, BallMaterial.Object);

	ConstructorHelpers::FObjectFinder<USoundCue> BallSound(TEXT("SoundCue'/Game/Audio/BallZing_Cue.BallZing_Cue'"));
	if (BallSound.Succeeded())
		Sound->SetSound(BallSound.Object);

	Ball->SetWorldScale3D(FVector(.5, .5, .5));

	Ball->SetSimulatePhysics(true);
	Ball->BodyInstance.bLockXRotation = true;
	Ball->BodyInstance.bLockYRotation = true;
	Ball->BodyInstance.bLockZRotation = true;
	Ball->SetMassOverrideInKg(NAME_None, .0001, true);
	Ball->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);

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

	Sound->Play();
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

void ABall::SetLastPlayerHit(int player)
{
	LastPlayerHit = player;
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
		//Ball->SetPhysicsLinearVelocity(GetVelocity().GetSafeNormal() * launchvelocity);
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
	if (!bIsOut)
	{
		FVector tossvel;
		UGameplayStatics::SuggestProjectileVelocity(this, tossvel, GetActorLocation(), destination, launchvelocity, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace);
		Ball->SetPhysicsLinearVelocity(tossvel);

		CurrentDestination = destination;
	}
}


float friction = 1;
float elasticity = 1;
void ABall::Deflect(FVector Normal)
{
	FVector Velocity = GetVelocity().GetSafeNormal() * 100;

	Normal.Normalize();

	FVector u = (FVector::DotProduct(Velocity, Normal)) * Normal;
	FVector w = Velocity - u;
	
	FVector NewVelocity = (friction * w) - (elasticity * u);

	UE_LOG(LogTemp, Log, TEXT("Setting Velocity After Deflect: %s"), *NewVelocity.ToString());

	Ball->SetPhysicsLinearVelocity(NewVelocity);
}