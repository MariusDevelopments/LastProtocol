// Copyright Epic Games, Inc. All Rights Reserved.

#include "LastProtocolGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "LastProtocolCharacter.h"
#include "ShooterAI.h"

ALastProtocolGameMode::ALastProtocolGameMode()
{
	// Projeye ozel varsayilan GameMode ayarlari Blueprint tarafinda veriliyor.
}

void ALastProtocolGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Level'daki oyuncu karakteri bulunur; AI'lara hedef olarak verilecektir.
	ALastProtocolCharacter* Player = Cast<ALastProtocolCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	TArray<AActor*> ShooterAIActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AShooterAI::StaticClass(), ShooterAIActors);

	// Level'daki tum ShooterAI controller'lari oyuncu referansi ile baslatilir.
	for (AActor* ShooterAIActor : ShooterAIActors) {
		AShooterAI* ShooterAI = Cast<AShooterAI>(ShooterAIActor);
		if (ShooterAI) {
			ShooterAI->StartBehaviorTree(Player);
		}
	}
}
