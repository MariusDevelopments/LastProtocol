// Copyright Epic Games, Inc. All Rights Reserved.


#include "LastProtocolPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "Blueprint/UserWidget.h"
#include "LastProtocol.h"
#include "LastProtocolCharacter.h"
#include "Widgets/Input/SVirtualJoystick.h"

void ALastProtocolPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Mobilde sanal kontrol widget'i yalnizca local player controller icin olusturulur.
	if (SVirtualJoystick::ShouldDisplayTouchInterface() && IsLocalPlayerController())
	{
		// Touch kontrol arayuzu spawn edilir.
		MobileControlsWidget = CreateWidget<UUserWidget>(this, MobileControlsWidgetClass);

		if (MobileControlsWidget)
		{
			// Kontroller oyuncu ekranina eklenir.
			MobileControlsWidget->AddToPlayerScreen(0);

		} else {

			UE_LOG(LogLastProtocol, Error, TEXT("Could not spawn mobile controls widget."));

		}

	}

	// Oyuncunun can barini gosteren HUD widget'i olusturulur.
	HUDWidget = CreateWidget<UHUDWidget>(this, HUDWidgetClass);
	if (HUDWidget)
	{
		HUDWidget->AddToViewport();

		if (ALastProtocolCharacter* LastProtocolCharacter = Cast<ALastProtocolCharacter>(GetPawn()))
		{
			LastProtocolCharacter->UpdateHUD();
		}
	}

}

void ALastProtocolPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Input Mapping Context'leri sadece local player controller'a eklenir.
	if (IsLocalPlayerController())
	{
		// Varsayilan Enhanced Input context'leri aktif edilir.
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}

			// Mobil touch kullanilmiyorsa mouse/klavye gibi ekstra context'ler eklenir.
			if (!SVirtualJoystick::ShouldDisplayTouchInterface())
			{
				for (UInputMappingContext* CurrentContext : MobileExcludedMappingContexts)
				{
					Subsystem->AddMappingContext(CurrentContext, 0);
				}
			}
		}
	}
}


