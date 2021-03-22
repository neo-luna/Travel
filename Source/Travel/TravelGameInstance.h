// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TravelGameInstance.generated.h"

/**
 *
 */
UCLASS()
class TRAVEL_API UTravelGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UTravelGameInstance(const FObjectInitializer & ObjectInitializer);

	/* Init our classes*/
	virtual void Init();

	class UUserWidget* PauseMenu;

	//class APlayerController*PlayerController;

	/* Function for adding widget to vieport*/
	UFUNCTION(BlueprintCallable)
		void ShowWidget();

	/* Function for hiding widget to vieport*/
	UFUNCTION(BlueprintCallable)
		void HideWidget();

	/* Reading in BP for Widget menu*/
	UPROPERTY(BlueprintReadWrite)
		int GIScore;

	UPROPERTY(BlueprintReadWrite)
		int GIBestScore;

	/* Tries of our PlayerShip*/
	int GIPlayerShipTries;

private:
	TSubclassOf<class UUserWidget>PauseMenuWidgetClass;

};
