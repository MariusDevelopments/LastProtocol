// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LastProtocolGameMode.generated.h"

/**
 * Oyun baslangicinda oyuncu ve AI arasindaki ilk baglantiyi kuran GameMode.
 */
UCLASS(abstract)
class ALastProtocolGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	/** Constructor */
	ALastProtocolGameMode();

protected:
	virtual void BeginPlay() override;
};



