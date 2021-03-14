// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

UCLASS()
class TRAVEL_API ASpawnVolume : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpawnVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent*SpawnVolume;

	UFUNCTION(BlueprintPure, Category = "Spawn")
		FVector RandomPointInVolume();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
		UClass* BP_Asteroid;

	UPROPERTY(EditAnywhere, BlueprintreadWrite, Category = "Spawn")
		UClass* BP_Bot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Timer")
		float SpawnDelayRangeLow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Timer")
		float SpawnDelayRangeHigh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Timer")
		float BotSpawnDelayRangeLow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Timer")
		float BotSpawnDelayRangeHigh;

	/* Function of spawning asteroids*/
	void SpawnAsteroid();

	/* Function of spawning bots*/
	void SpawnBot();

	class AAsteroid*Asteroid;

	class ABot*Bot;

	FTimerHandle SpawnTimer;

	FTimerHandle BotSpawnTimer;

	float SpawnDelay;

	float BotSpawnDelay;
};
