// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"

void UHUDWidget::SetHealthBarPercent(float NewPercent)
{
	// ProgressBar yalnizca 0-1 arasi yuzde bekledigi icin degeri sinirliyoruz.
	const float ClampedPercent = FMath::Clamp(NewPercent, 0.0f, 1.0f);

	if (HealthBar)
	{
		HealthBar->SetPercent(ClampedPercent);
	}

	if (HealthPercentText)
	{
		const int32 PercentValue = FMath::RoundToInt(ClampedPercent * 100.0f);
		HealthPercentText->SetText(FText::FromString(FString::Printf(TEXT("%d%%"), PercentValue)));
	}
}
