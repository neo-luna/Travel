// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Asteroid.generated.h"

UCLASS()
class TRAVEL_API AAsteroid : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAsteroid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Asteroid")
		class UCapsuleComponent*Capsule;

	UPROPERTY(EditAnywhere, Category = "Asteroid")
		class UStaticMeshComponent*Mesh;

	/* Value of min asteroid velocity*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Asteroid velocity")
		float MinVal;

	/* Value of max asteroid velocity*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Asteroid velocity")
		float MaxVal;

	//Overlapping Destroy with Projectile, Bot, BotProjectile, Asteroid
	UFUNCTION()
		void DestroyOverlap(AActor* OtherActor, AActor* OverlappedActor);

	//Casting GameInstance
	void CastGameInstance();

	class UGameInstance*GameInstance;
	class UTravelGameInstance*TravelGameInstance;

	class APlayerShip* PlayerShip;

	FVector AsteroidLocation;

	float VelocityRange;

	float RotationRange;

	//Quantity of Asteroid
	int Quantity;



};

