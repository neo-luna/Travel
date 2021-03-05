// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetForBot.h"
#include "Components/SphereComponent.h"

// Sets default values
ATargetForBot::ATargetForBot()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetHiddenInGame(false);
	Sphere->InitSphereRadius(50);
	RootComponent = Sphere;

	Direction = 1;
}

// Called when the game starts or when spawned
void ATargetForBot::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATargetForBot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move();

}

void ATargetForBot::Move()
{
	NewLocation = GetActorLocation();
	if (NewLocation.Y >= 350)
	{
		Direction = Direction * -1;
	}
	if (NewLocation.Y <= -350)
	{
		Direction = Direction * -1;
	}
	NewLocation.Y += Direction;
	SetActorLocation(NewLocation);
}

