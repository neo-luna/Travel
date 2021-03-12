// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerShip.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Asteroid.h"
#include "Bot.h"
#include "BotProjectile.h"
#include "TravelGameInstance.h"
#include "Materials/MaterialInterface.h"
#include "TravelSaveGame.h"

// Sets default values
APlayerShip::APlayerShip()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	RootComponent = Sphere;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Sphere);

	TurbineFireLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurbineFireLeft"));
	TurbineFireLeft->SetupAttachment(Sphere);

	TurbineFireRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurbineFireRight"));
	TurbineFireRight->SetupAttachment(Sphere);

	GreenMat = CreateDefaultSubobject<UMaterial>(TEXT("GreenMat"));
	YellowMat = CreateDefaultSubobject<UMaterial>(TEXT("YellowMat"));
	RedMat = CreateDefaultSubobject<UMaterial>(TEXT("RedMat"));

	Velocity = 500;

	Tries = 3;

	bCheck = true;

	bFire = false;
}

// Called when the game starts or when spawned
void APlayerShip::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &APlayerShip::DestroyOverlap);

	Mesh->SetMaterial(1, GreenMat);

	/* Start PlayerShip location*/
	SetActorLocation(FVector(Start_Location, 0, 0));

	CastGameInstance();

	GetWorldTimerManager().SetTimer(FireHandle, this, &APlayerShip::FireSwitch, FireDelay, true);

	GetWorldTimerManager().SetTimer(PulseHandle, this, &APlayerShip::PulsingScale, TimePulsing, true);

	/* Resets GIScore because GIScore equals 1 in start game...*/
	TravelGameInstance->GIScore = 0;

	ScoreCheck = false;

	PauseTurn = 1;

	PulsingValue = 1;

	ScaleValue = 1.0;

	LoadScore();
}

// Called every frame
void APlayerShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!CurrentVelocity.IsZero())
	{
		FVector NewLocation = GetActorLocation() + (CurrentVelocity*DeltaTime);
		SetActorLocation(NewLocation);
	}
	
	ConstraintMoving();

	DestroyPlayerShip();

	ChangeMaterial();

	CheckScore();

	RayCastingFunction();
}

// Called to bind functionality to input
void APlayerShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerShip::MoveRight);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerShip::MoveForward);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerShip::Fire);

	/* If press - ScaleTurbineFire, if unpress -  not ScaleTurbineFire*/
	PlayerInputComponent->BindAction("ScaleTurbineFire", IE_Pressed, this, &APlayerShip::ScaleTurbineFire);
	PlayerInputComponent->BindAction("ScaleTurbineFire", IE_Released, this, &APlayerShip::UnScaleTurbineFire);

	FInputActionBinding& Toggle = PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &APlayerShip::Pause);
	Toggle.bExecuteWhenPaused = true;
}

/* BLOCK of PlayerShip */
void APlayerShip::DestroyOverlap(AActor * OtherActor, AActor * OverlappedActor)
{
	if (Cast<AAsteroid>(OverlappedActor) != nullptr)
	{
		Tries = Tries -= 1;
	}
	if (Cast<ABot>(OverlappedActor) != nullptr)
	{
		Tries = Tries -= 1;
	}
	if (Cast<ABotProjectile>(OverlappedActor) != nullptr)
	{
		Tries = Tries -= 1;
	}
}
void APlayerShip::DestroyPlayerShip_Implementation()
{
	if (Tries == 0)
	{
		SaveScore();

		Destroy();
	}
}
void APlayerShip::MoveRight(float AxisValue)
{
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.f, 1.f) * Velocity;

	SetActorRotation(FRotator(0, 0, 45 * AxisValue));
}
void APlayerShip::MoveForward(float AxisValue)
{
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.f, 1.f) * Velocity;
}
void APlayerShip::ConstraintMoving()
{
	//Constraint of moving out of borders
	FVector ActorLocation = GetActorLocation();

	if (ActorLocation.Y <= -650)
	{
		ActorLocation.Y = -650;
		SetActorLocation(ActorLocation);
	}
	if (ActorLocation.Y >= 650)
	{
		ActorLocation.Y = 650;
		SetActorLocation(ActorLocation);
	}
	if (ActorLocation.X <= -1250)
	{
		ActorLocation.X = -1220;
		SetActorLocation(ActorLocation);
	}
	if (ActorLocation.X >= 1250)
	{
		ActorLocation.X = 1250;
		SetActorLocation(ActorLocation);
	}
}

/* BLOCK of TurbineFire*/
void APlayerShip::ScaleTurbineFire()
{
	ScaleValue = 1.5;	
}
void APlayerShip::UnScaleTurbineFire()
{
	ScaleValue = 1.0;
}
void APlayerShip::PulsingScale()
{
	float PulsingScale;

	PulsingValue = PulsingValue * -1;

	if (PulsingValue == 1)
	{
		PulsingScale = 1.0f * ScaleValue;
		TurbineFireLeft->SetRelativeScale3D(FVector(PulsingScale, PulsingScale, PulsingScale));
		TurbineFireRight->SetRelativeScale3D(FVector(PulsingScale, PulsingScale, PulsingScale));
	}
	if (PulsingValue == -1)
	{
		PulsingScale = 1.2f * ScaleValue;
		TurbineFireLeft->SetRelativeScale3D(FVector(PulsingScale, PulsingScale, PulsingScale));
		TurbineFireRight->SetRelativeScale3D(FVector(PulsingScale, PulsingScale, PulsingScale));
	}
}

/* BLOCK of materials*/
void APlayerShip::ChangeMaterial()
{
	/* Change color of PlayerShip*/
	if (Tries == 2)
	{
		Mesh->SetMaterial(1, YellowMat);
	}
	if (Tries == 1)
	{
		Mesh->SetMaterial(1, RedMat);
	}
}

/* BLOCK of GameInstance casting*/
void APlayerShip::CastGameInstance()
{
	GameInstance = GetWorld()->GetGameInstance();
	TravelGameInstance = Cast<UTravelGameInstance>(GameInstance);
}

/* BLOCK of shooting */
void APlayerShip::Fire()
{
	AProjectile*Projectile;

	FVector ActorForwardVector = GetActorForwardVector();
	FVector Start = GetActorLocation();
	Start += ActorForwardVector;

	//Switch fire to on/of
	if (bFire)
	{
		bFire = false;
		Projectile = GetWorld()->SpawnActor<AProjectile>(BP_Projectile, Start, RootComponent->GetComponentRotation());
	}
}
void APlayerShip::FireSwitch()
{
	bFire = true;
}
void APlayerShip::RayCastingFunction()
{
	FVector ActorLocation = GetActorLocation();
	FHitResult Hit;
	FVector ForwardVector = GetActorForwardVector();
	FVector End = (ForwardVector * 2000) + ActorLocation;
	
	if (GetWorld()->LineTraceSingleByChannel(Hit, ActorLocation, End, ECC_Visibility))
	{
		if (Cast<ABot>(Hit.Actor) || Cast<AAsteroid>(Hit.Actor))
		{
			Fire();
		}
	}
}

/* BLOCK of gameplay */
void APlayerShip::Pause()
{

	PauseTurn = PauseTurn * -1;

	if (PauseTurn == -1)
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);

		TravelGameInstance->ShowWidget();
	}
	if (PauseTurn == 1)
	{
		UGameplayStatics::SetGamePaused(GetWorld(), false);

		TravelGameInstance->HideWidget();
	}
}
void APlayerShip::CheckScore()
{
	/* If GIScore = 0 and  ScoreCheck = true PlayerShip is destroyed*/
	if (TravelGameInstance->GIScore < 0)
	{
		TravelGameInstance->GIScore = 0;

		Tries = 0;
	}

	if (TravelGameInstance->GIScore > 0)
	{
		ScoreCheck = true;
	}
	if (TravelGameInstance->GIScore == 0 && ScoreCheck == true)
	{
		TravelGameInstance->GIScore = 0;

		Tries = 0;
	}

}
void APlayerShip::SaveScore()
{
	/* Calling after PlayerShip destroy*/
	class UTravelSaveGame*SaveGameInstance = Cast<UTravelSaveGame>(UGameplayStatics::CreateSaveGameObject(UTravelSaveGame::StaticClass()));

	if (true)
	{
		if (TravelGameInstance->GIScore > TravelGameInstance->GIBestScore)
		{
			TravelGameInstance->GIBestScore = TravelGameInstance->GIScore;

			SaveGameInstance->PlayerShipScore = TravelGameInstance->GIBestScore;
			UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->PlayerShipSlotName, SaveGameInstance->PlayerShipIndex);
		}
		
	}
}
void APlayerShip::LoadScore()
{
	class UTravelSaveGame*LoadGameInstance = Cast<UTravelSaveGame>(UGameplayStatics::CreateSaveGameObject(UTravelSaveGame::StaticClass()));

	LoadGameInstance = Cast<UTravelSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->PlayerShipSlotName, LoadGameInstance->PlayerShipIndex));

	if (LoadGameInstance)
	{
		TravelGameInstance->GIBestScore = LoadGameInstance->PlayerShipScore;
	}
}