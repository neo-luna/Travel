// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerShip.generated.h"

UCLASS()
class TRAVEL_API APlayerShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerShip();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/* BLOCK of PlayerShip */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Properties")
		class USphereComponent*Sphere;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Properties")
		class UStaticMeshComponent*Mesh;
	/* Start location of PlayerShip */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Properties")
		float Start_Location;
	/* Just velosity of PlayerShip */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Properties")
		float Velocity;
	/* Overlapping PlayerShip */
	UFUNCTION()
		void DestroyOverlap(AActor*OtherActor, AActor* OverlappedActor);
	/*If Tries = 0, PlayerShip destroy */
	UFUNCTION(BlueprintNativeEvent)
		void DestroyPlayerShip();
	/* Moving functions*/
	void MoveRight(float AxisValue);
	void MoveForward(float AxisValue);
	/* Constraint of moving PlayerShip*/
	void ConstraintMoving();
	FVector CurrentVelocity;

	/* BLOCK of TurbineFire*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turbine Fire Properties")
		class UStaticMeshComponent* TurbineFireLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turbine Fire Properties")
		class UStaticMeshComponent* TurbineFireRight;
	/* Value of time pulsing*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turbine Fire Properties")
		float TimePulsing = 0.1f;
	/* Scaling turbines fire*/
	void ScaleTurbineFire();
	void UnScaleTurbineFire();
	/*Pulsing scaling of turbine fire*/
	void PulsingScale();
	/* Handle of selfpulsing of turbine fire*/
	FTimerHandle PulseHandle;
	/* Scale a fire of turbine when button of moving pressed */
	float ScaleValue;  // Value of scaling
	/* Flag for change pulsing*/
	int PulsingValue;

	/* BLOCK of materials*/
	UPROPERTY(EditAnywhere)
		class UMaterial* GreenMat;
	UPROPERTY(EditAnywhere)
		class UMaterial* YellowMat;
	UPROPERTY(EditAnywhere)
		class UMaterial* RedMat;
	/* Change material function*/
	void ChangeMaterial();

	/* BLOCK of GameInstance casting*/
	class UGameInstance*GameInstance;
	class UTravelGameInstance*TravelGameInstance;
	//Casting GameInstance
	void CastGameInstance();

	/* BLOCK of shooting */
	/* PlayerShip projectile */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Properties")
		UClass*BP_Projectile;
	/* Delay of fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Properties")
		float FireDelay;
	/* Fire function */
	void Fire();
	/* Switch fire */
	void FireSwitch();
	/* Automatic fire function */
	void RayCastingFunction();
	/* Time fire handle */
	FTimerHandle FireHandle;
	/* Fire or not?*/
	bool bFire;
	/* Checking fire */
	bool bCheck;

	/* BLOCK of gameplay */
	/* Custom pause function */
	UFUNCTION(BlueprintCallable)
		void Pause();
	/* Checking value of GIScore */
	void CheckScore();
	/* Number of tries */
	int Tries;
	/* Turn On/Off CuastomPause function */
	int PauseTurn;
	/* Flag to checking GIScore*/
	bool ScoreCheck;
	/* Save/Load Score*/
	UFUNCTION(BlueprintCallable)
		void SaveScore();
	void LoadScore();
};
