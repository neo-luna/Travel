// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Asteroid.h"
#include "DestroyVolume.h"
#include "Bot.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetHiddenInGame(false);
	RootComponent = Sphere;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Sphere);

	Velocity = 5;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &AProjectile::DestroyOverlap);

	GetWorldTimerManager().SetTimer(HandleDestroy, this, &AProjectile::Destroing, TimeDestroy, true);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move();
}

/* BLOCK of Projectile */
void AProjectile::DestroyOverlap(AActor * OtherActor, AActor * OverlappedActor)
{
	/* Overlapping with Bot, DestroyVolume, Asteroid*/
	if (Cast<AAsteroid>(OverlappedActor) != nullptr || Cast<ADestroyVolume>(OverlappedActor) != nullptr || Cast<ABot>(OverlappedActor) != nullptr)
	{
		Destroy();
	}
}
void AProjectile::Move()
{
	SetActorLocation(GetActorLocation() + GetActorForwardVector() * Velocity);
}

/* BLOCK of destroing after time*/
void AProjectile::Destroing()
{
	Destroy();
}


