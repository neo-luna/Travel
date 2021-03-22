// Fill out your copyright notice in the Description page of Project Settings.


#include "Bot.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TravelGameInstance.h"
#include "Projectile.h"
#include "PlayerShip.h"
#include "DestroyVolume.h"
#include "BotProjectile.h"
#include "TargetForBot.h"

// Sets default values
ABot::ABot()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->InitSphereRadius(50);
	RootComponent = Sphere;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Sphere);

	BotTurbineFire = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BotTurbineFire"));
	BotTurbineFire->SetupAttachment(Sphere);

	Quantity = 1; // "Quantity" of Bot

	MinBotVelocity = 3.0;

	MaxBotVelocity = 5.0;

	PulsingValue = 1;
}

// Called when the game starts or when spawned
void ABot::BeginPlay()
{
	Super::BeginPlay();

	CastGameInstance();

	OnActorBeginOverlap.AddDynamic(this, &ABot::DestroyOverlap);

	GetWorldTimerManager().SetTimer(FireHandle, this, &ABot::Fire, TimeFireDelay, true, TimeFireStart);

	GetWorldTimerManager().SetTimer(PulseHandle, this, &ABot::PulsingScale, TimePulsing, true);
}

// Called every frame
void ABot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FoundPlayerShip();

	/* if the PlayerShip is destroyed, the Quantity of the Bot is 0*/

	if (TravelGameInstance->GIPlayerShipTries == 0)
	{
		Quantity = 0;
	}
}

/* BLOCK of Bot */
void ABot::DestroyOverlap(AActor * OtherActor, AActor * OverlappedActor)
{
	/* Destroy bot with overlapping Projectile,DestroyVolume,PlayerShip*/
	if (Cast<AProjectile>(OverlappedActor) != nullptr)
	{
		TravelGameInstance->GIScore += Quantity;

		Destroy();
	}
	if (Cast<APlayerShip>(OverlappedActor) != nullptr)
	{
		/*The cost of a Bot is reset to zero before being destroyed*/

		Quantity = 0;

		Destroy();
	}
	if (Cast<ADestroyVolume>(OverlappedActor) != nullptr)
	{
		TravelGameInstance->GIScore -= Quantity;

		Destroy();
	}
}
void ABot::Move()
{
	/* Different Bot velocity from range*/
	float VelocityRange = FMath::FRandRange(MinBotVelocity, MaxBotVelocity);

	SetActorLocation(GetActorLocation() + (GetActorForwardVector() * VelocityRange));
}
void ABot::FoundPlayerShip()
{
	/* Finding PlayerShip in World*/
	TSubclassOf<ATargetForBot> ClassToFind;
	ClassToFind = ATargetForBot::StaticClass();
	TArray<AActor*> FoundEnemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToFind, FoundEnemies);

	/* Finding diastance between Actors*/
	for (AActor* Actor : FoundEnemies)
	{
		TargetPlayerLocation = Actor->GetActorLocation();

		ToPlayer = TargetPlayerLocation - GetActorLocation();

		DistanceToPlayer = ToPlayer.Size();
	}

	/* Set rotation of Bot*/
	FVector BotLocation = GetActorLocation();
	FLAR = UKismetMathLibrary::FindLookAtRotation(BotLocation, TargetPlayerLocation);
	BotRotation = UKismetMathLibrary::MakeRotator(0, 0, FLAR.Yaw);

	SetActorRelativeRotation(BotRotation);

	if (DistanceToPlayer >= Sphere->GetScaledSphereRadius())
	{
		Move();
	}
}

/* BLOCK of TurbineFire*/
void ABot::PulsingScale()
{
	float PulsingScale;

	PulsingValue = PulsingValue * -1;

	if (PulsingValue == 1)
	{
		PulsingScale = 0.35f;
		BotTurbineFire->SetRelativeScale3D(FVector(PulsingScale, PulsingScale, PulsingScale));
	}
	if (PulsingValue == -1)
	{
		PulsingScale = 0.5f;
		BotTurbineFire->SetRelativeScale3D(FVector(PulsingScale, PulsingScale, PulsingScale));
	}
}

/* BLOCK of shooting*/
void ABot::Fire()
{
	/* Set a spawn position of BatProjectile*/
	FVector ForwardVector = GetActorForwardVector();
	FVector Start = GetActorLocation();
	Start += ForwardVector * 100;

	BotProjectile = GetWorld()->SpawnActor<ABotProjectile>(BP_BotProjectile, Start, RootComponent->GetComponentRotation());
}

/* BLOCK of casting GameInstance*/
void ABot::CastGameInstance()
{
	GameInstance = GetWorld()->GetGameInstance();
	TravelGameInstance = Cast<UTravelGameInstance>(GameInstance);
}

