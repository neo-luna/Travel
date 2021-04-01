// Fill out your copyright notice in the Description page of Project Settings.


#include "TravelGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"

//Constructor
UTravelGameInstance::UTravelGameInstance(const FObjectInitializer & ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget>PauseMenuWidget(TEXT("/Game/INTERFACE/WB_PauseMenu"));
	if (!ensure(PauseMenuWidget.Class != nullptr)) return;

	PauseMenuWidgetClass = PauseMenuWidget.Class;

}

void UTravelGameInstance::Init()
{
	
	GIScore = 0;
	GIBestScore = 0;

	UE_LOG(LogTemp, Warning, TEXT("We are founded class %s "), *PauseMenuWidgetClass->GetName());
}

void UTravelGameInstance::ShowWidget()
{
	PauseMenu = CreateWidget<UUserWidget>(this, PauseMenuWidgetClass);
	PauseMenu->AddToViewport();

	APlayerController*PlayerController = GetFirstLocalPlayerController();
	/* Set InputMode function*/
	FInputModeGameAndUI InputModeData;
	InputModeData.SetWidgetToFocus(PauseMenu->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = true;
}

void UTravelGameInstance::HideWidget()
{
	APlayerController*PlayerController = GetFirstLocalPlayerController();

	// Set InputMode function
	FInputModeGameOnly InputModeData;
	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = false;

	PauseMenu->SetVisibility(ESlateVisibility::Collapsed);
}

