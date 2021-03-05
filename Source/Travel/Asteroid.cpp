// Fill out your copyright notice in the Description page of Project Settings.


#include "Asteroid.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PlayerShip.h"
#include "Kismet/KismetMathLibrary.h"
#include "Projectile.h"
#include "Bot.h"
#include "BotProjectile.h"
#include "TravelGameInstance.h"
#include "DestroyVolume.h"

// Sets default values
AAsteroid::AAsteroid()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = Capsule;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Capsule);

	MinVal = 2;
	MaxVal = 5;

	Quantity = 1;
}

// Called when the game starts or when spawned
void AAsteroid::BeginPlay()
{
	Super::BeginPlay();

	CastGameInstance();

	/*scale an asteroid*/
	float ScaleParam = FMath::FRandRange(1.5, 3.6);
	SetActorScale3D(FVector(ScaleParam, ScaleParam, ScaleParam));

	/*range velocity an asteroid*/
	VelocityRange = FMath::FRandRange(MinVal, MaxVal);

	/*range rotation an asteroid*/
	RotationRange = FMath::FRandRange(-0.3, 0.3);

	OnActorBeginOverlap.AddDynamic(this, &AAsteroid::DestroyOverlap);
}

// Called every frame
void AAsteroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*movement an asteroid*/
	AsteroidLocation = GetActorLocation();
	AsteroidLocation.X -= VelocityRange;
	SetActorLocation(AsteroidLocation);

	/*rotation an asteroid*/
	FRotator AsteroidRotation = GetActorRotation();
	AsteroidRotation.Yaw += 1.1*RotationRange;
	SetActorRotation(AsteroidRotation);

	/* if the PlayerShip is destroyed, the Quantity of the Asteroid is 0*/
	for (TObjectIterator<APlayerShip> It; It; ++It)
	{
		PlayerShip = *It;

		if (PlayerShip->Tries == 0)
		{
			Quantity = 0;
		}
	}
}

void AAsteroid::DestroyOverlap(AActor * OtherActor, AActor * OverlappedActor)
{
	if (Cast<AProjectile>(OverlappedActor) != nullptr)
	{
		TravelGameInstance->GIScore += Quantity;

		Destroy();
	}
	if (Cast<APlayerShip>(OverlappedActor) != nullptr
		|| Cast<ABot>(OverlappedActor) != nullptr || Cast<ABotProjectile>(OverlappedActor) != nullptr)

	{
		/* The cost of an Asteroid is reset to zero before being destroyed*/
		Quantity = 0;

		Destroy();
	}
	/* If Asteroid destroing from DestroyVolume - subtract Quantity from GIScore*/
	if (Cast<ADestroyVolume>(OverlappedActor) != nullptr)
	{
		TravelGameInstance->GIScore -= Quantity;

		Destroy();
	}

	/* Destroy Asteroid with self overlapping*/
	float FirstDestroyValue = FMath::FRandRange(1.0, 5.0);
	float SecondDestroyValue = FMath::FRandRange(1.0, 5.0);

	if (Cast<AAsteroid>(OverlappedActor) != nullptr)
	{
		if (FirstDestroyValue >= SecondDestroyValue)
		{
			Quantity = 0;
			Destroy();
		}
	}
}

//Casting GameInstance
void AAsteroid::CastGameInstance()
{
	GameInstance = GetWorld()->GetGameInstance();
	TravelGameInstance = Cast<UTravelGameInstance>(GameInstance);
}