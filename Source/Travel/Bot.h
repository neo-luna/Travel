// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bot.generated.h"

UCLASS()
class TRAVEL_API ABot : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* BLOCK of Bot */
	UPROPERTY(EditAnywhere, Category = "Bot")
		class USphereComponent* Sphere;
	UPROPERTY(EditAnywhere, Category = "Bot")
		class UStaticMeshComponent* Mesh;
	/* Overlapping*/
	UFUNCTION()
		void DestroyOverlap(AActor* OtherActor, AActor* OverlappedActor);
	/* Min Bot velocity*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bot")
		float MinBotVelocity;
	/* Max Bot velocity*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bot")
		float MaxBotVelocity;
	/* Moving Bot*/
	void Move();
	/* Finding and rotating Bot to PlayerShip*/
	void FoundPlayerShip();
	/* Quantity of Bot */
	int Quantity;

	/* BLOCK of TurbineFire*/
	UPROPERTY(EditAnywhere, Category = "Bot")
		class UStaticMeshComponent* BotTurbineFire;
	/*Pulsing scaling of turbine fire*/
	void PulsingScale();
	/* Handle of selfpulsing of turbine fire*/
	FTimerHandle PulseHandle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimerSettings")
		float TimePulsing = 0.1f;
	/* Flag for change pulsing*/
	int PulsingValue;

	/* BLOCK of shooting*/
	/* Bot projectile object*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bot")
		UClass* BP_BotProjectile;
	/* Starting fire*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BotProjectileSettings")
		float TimeFireStart;
	/* Step of Fire*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BotProjectileSettings")
		float TimeFireDelay;
	/* Fire function*/
	void Fire();
	FTimerHandle FireHandle;

	/* BLOCK of casting GameInstance*/
	/* Casting GameInstance*/
	void CastGameInstance();
	class UGameInstance*GameInstance;
	class UTravelGameInstance*TravelGameInstance;

	/* BLOCK of searching target */
	FVector TargetPlayerLocation; // Player who will a target for Bot
	FVector ToPlayer;
	FRotator FLAR;
	FRotator BotRotation;
	float DistanceToPlayer;

	/* Including games entities*/
	class APlayerShip* PlayerShip;
	class ATargetForBot* TargetForBot;
	class ABotProjectile* BotProjectile;

	



	


};
