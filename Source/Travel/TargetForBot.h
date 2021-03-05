// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetForBot.generated.h"

UCLASS()
class TRAVEL_API ATargetForBot : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATargetForBot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "TargetSettings")
		class USphereComponent* Sphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="TargetSettings" )
		float Direction;

	/* Moving target function*/
	void Move();

	FVector NewLocation;

	

};
