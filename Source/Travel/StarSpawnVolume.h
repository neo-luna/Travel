// Travel v.0.0

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StarSpawnVolume.generated.h"

UCLASS()
class TRAVEL_API AStarSpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStarSpawnVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Star SpawnVolume Settings")
		class UBoxComponent* SpawnVolume;

	UPROPERTY(EditDefaultsOnly, Category = "Star SpawnVolume Settings")
		UClass*BP_Star;
	
	UFUNCTION(BlueprintPure, Category = "Star SpawnVolume Settings")
		FVector RandomPointInVolume();

	void SpawnStars();

	class AStar*Star;

	float StarScale;
};
