// Travel v.0.0

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Star.generated.h"

UCLASS()
class TRAVEL_API AStar : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "StarSettings")
		class USphereComponent* Sphere;

	UPROPERTY(EditAnywhere, Category = "StarSettings")
		class UStaticMeshComponent* Mesh;

	float FirstScale;

	float SecondScale;

	float ResultScale;
};
