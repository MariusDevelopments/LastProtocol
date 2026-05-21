// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "HUDWidget.generated.h"


/**
 * Oyuncu arayuzundeki saglik barini kontrol eden widget sinifi.
 */
UCLASS()
class LASTPROTOCOL_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// WBP_HUD icindeki ProgressBar ile ayni isimdeyse otomatik baglanir.
	UPROPERTY(EditAnywhere, meta = (BindWidgetOptional))
	UProgressBar* HealthBar;

	// WBP_HUD icindeki TextBlock ile ayni isimdeyse otomatik baglanir.
	UPROPERTY(EditAnywhere, meta = (BindWidgetOptional))
	UTextBlock* HealthPercentText;

	// 0.0 - 1.0 arasi can yuzdesini progress bar'a ve yuzde yazisina uygular.
	void SetHealthBarPercent(float NewPercent);
	
};
