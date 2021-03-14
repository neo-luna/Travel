// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnVolume.h"
#include "Components/BoxComponent.h"
#include "Asteroid.h"
#include "Bot.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ASpawnVolume::ASpawnVolume()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	SpawnVolume->SetHiddenInGame(false);
	SpawnVolume->InitBoxExtent(FVector(100, 500, 5));
	RootComponent = SpawnVolume;

	SpawnDelayRangeLow = 1.0;
	SpawnDelayRangeHigh = 2.5;

	BotSpawnDelayRangeLow = 2.0;
	BotSpawnDelayRangeHigh = 3.5;
}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(FVector(2000, 0, 0));

	SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnAsteroid, SpawnDelay, false);

	BotSpawnDelay = FMath::FRandRange(BotSpawnDelayRangeLow, BotSpawnDelayRangeHigh);
	GetWorldTimerManager().SetTimer(BotSpawnTimer, this, &ASpawnVolume::SpawnBot, BotSpawnDelay, false);
}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FVector ASpawnVolume::RandomPointInVolume()
{
	FVector SpawnOrigin = SpawnVolume->Bounds.Origin;
	FVector SpawnExtent = SpawnVolume->Bounds.BoxExtent;

	return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);
}

void ASpawnVolume::SpawnAsteroid()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();
	FVector SpawnLocation = RandomPointInVolume();

	FRotator SpawnRotation;
	SpawnRotation.Yaw = FMath::FRand() * 360;
	SpawnRotation.Pitch = FMath::FRand() * 360;
	SpawnRotation.Roll = FMath::FRand() * 360;

	Asteroid = GetWorld()->SpawnActor<AAsteroid>(BP_Asteroid, SpawnLocation, SpawnRotation, SpawnParams);

	SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnAsteroid, SpawnDelay, false);
}

void ASpawnVolume::SpawnBot()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();
	FVector SpawnLocation = RandomPointInVolume();

	Bot = GetWorld()->SpawnActor<ABot>(BP_Bot, SpawnLocation, RootComponent->GetComponentRotation(), SpawnParams);

	BotSpawnDelay = FMath::FRandRange(BotSpawnDelayRangeLow, BotSpawnDelayRangeHigh);
	GetWorldTimerManager().SetTimer(BotSpawnTimer, this, &ASpawnVolume::SpawnBot, BotSpawnDelay, false);
}
