// Fill out your copyright notice in the Description page of Project Settings.


#include "BotProjectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PlayerShip.h"

// Sets default values
ABotProjectile::ABotProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetHiddenInGame(false);
	Sphere->InitSphereRadius(15);
	RootComponent = Sphere;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Sphere);

	Velocity = 5;
}

// Called when the game starts or when spawned
void ABotProjectile::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ABotProjectile::PlayerShipOverlap);

	GetWorldTimerManager().SetTimer(HandleDestroy, this, &ABotProjectile::Destroing, TimeDestroy, true);
}

// Called every frame
void ABotProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move();
}

/* BLOCK of BotProjectile */
void ABotProjectile::PlayerShipOverlap(AActor * OverlappedActor, AActor * OtherActor)
{
	/* Destroy if overlapping with PlayerShip*/
	if (Cast<APlayerShip>(OtherActor))
	{
		Destroy();
	}
}
void ABotProjectile::Move()
{
	SetActorLocation(GetActorLocation() + GetActorForwardVector() * Velocity);
}

/* BLOCK of destroing after time*/
void ABotProjectile::Destroing()
{
	/* Destroy after time*/
	Destroy();
}


