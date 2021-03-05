// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TRAVEL_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* BLOCK of Projectile */
	UPROPERTY(EditAnywhere, Category = "ProjectileSettings")
		class USphereComponent* Sphere;
	UPROPERTY(EditAnywhere, Category = "ProjectileSettings")
		class UStaticMeshComponent* Mesh;
	/* Destroy overlapping*/
	UFUNCTION()
		void DestroyOverlap(AActor* OtherActor, AActor* OverlappedActor);
	/* Velocity of Projectile*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BotProjectileSettings")
		float Velocity;
	/* Moving function */
	void Move();
	/* Location of PlayerShip for start */
	FVector ActorLocation;

	/* BLOCK of destroing after time*/
	/* Time destroing*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BotProjectileSettings")
		float TimeDestroy;
	/* Destroing Projectile after time*/
	void Destroing();
	FTimerHandle HandleDestroy;

	
};
