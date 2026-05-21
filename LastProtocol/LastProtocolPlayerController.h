// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HUDWidget.h"
#include "LastProtocolPlayerController.generated.h"

class UInputMappingContext;
class UUserWidget;

/**
 * Oyuncu controller'i input mapping ve HUD olusturma islerinden sorumludur.
 */
UCLASS(abstract)
class ALastProtocolPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category ="Input|Input Mappings")
	TArray<UInputMappingContext*> DefaultMappingContexts;

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category="Input|Input Mappings")
	TArray<UInputMappingContext*> MobileExcludedMappingContexts;

	/** Mobile controls widget to spawn */
	UPROPERTY(EditAnywhere, Category="Input|Touch Controls")
	TSubclassOf<UUserWidget> MobileControlsWidgetClass;

	/** Pointer to the mobile controls widget */
	TObjectPtr<UUserWidget> MobileControlsWidget;


	/** Gameplay initialization */
	virtual void BeginPlay() override;

	/** Input mapping context setup */
	virtual void SetupInputComponent() override;
public:
	// Blueprint'te secilen HUD widget sinifi.
	UPROPERTY(EditAnywhere)
	TSubclassOf<UHUDWidget> HUDWidgetClass;

	// Oyun sirasinda olusturulan HUD widget referansi.
	UPROPERTY(VisibleAnywhere)
	UHUDWidget* HUDWidget;

};
