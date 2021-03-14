// Travel v.0.0

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "TravelSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class TRAVEL_API UTravelSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
		
	UTravelSaveGame();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Save Settings")
		int32 PlayerShipScore;

	UPROPERTY(VisibleAnywhere, Category = "Save Settings")
		FString PlayerShipName;

	UPROPERTY(VisibleAnywhere, Category = "Save Settings")
		FString PlayerShipSlotName;

	UPROPERTY(VisibleAnywhere, Category = "Save Settings")
		uint32 PlayerShipIndex;
};
