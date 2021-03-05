// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BotProjectile.generated.h"

UCLASS()
class TRAVEL_API ABotProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABotProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* BLOCK of BotProjectile */
	UPROPERTY(EditAnywhere, Category = "BotProjectileSettings")
		class USphereComponent* Sphere;
	UPROPERTY(EditAnywhere, Category = "BotProjectileSettings")
		class UStaticMeshComponent* Mesh;
	/* Destroy overlapping */
	UFUNCTION()
		void PlayerShipOverlap(AActor* OverlappedActor, AActor* OtherActor);
	/* Velocity of BotProjectile*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BotProjectileSettings")
		float Velocity;
	/* Moving function*/
	void Move();

	/* BLOCK of destroing after time*/
	/* Time destroing*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BotProjectileSettings")
		float TimeDestroy;
	void Destroing();
	FTimerHandle HandleDestroy;


};
