// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "LastProtocolCharacter.h"
#include "ShooterAI.generated.h"

/**
 * Dusman karakterleri yoneten AIController.
 * Behavior Tree'yi baslatir ve oyuncu/AI karakter referanslarini saklar.
 */
UCLASS()
class LASTPROTOCOL_API AShooterAI : public AAIController
{
	GENERATED_BODY()


protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UBehaviorTree* EnemeyAIBehaviorTree;

	// AI'nin takip edip ates edecegi oyuncu karakteri.
	ALastProtocolCharacter* PlayerCharacter;

	// Bu controller'in kontrol ettigi dusman karakter.
	ALastProtocolCharacter* MyCharacter;


	// GameMode tarafindan oyuncu referansi verilince Behavior Tree akisini baslatir.
	void StartBehaviorTree(ALastProtocolCharacter* Player);

	
};
