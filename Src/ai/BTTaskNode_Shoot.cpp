// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Shoot.h"
#include "ShooterAI.h"

UBTTaskNode_Shoot::UBTTaskNode_Shoot()
{
	// Behavior Tree editor'unde node bu isimle gorunur.
	NodeName = TEXT("Shoot At Player");

}

EBTNodeResult::Type UBTTaskNode_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	EBTNodeResult::Type Result = EBTNodeResult::Failed;

	// Task'i calistiran AIController bizim AShooterAI sinifimiz olmali.
	AShooterAI* OwnerController = Cast<AShooterAI>(OwnerComp.GetAIOwner());
	if (OwnerController) {
		ALastProtocolCharacter* OwnerCharacter = OwnerController->MyCharacter;
		ALastProtocolCharacter* PlayerCharacter = OwnerController->PlayerCharacter;

		// AI ve oyuncu referanslari gecerliyse, oyuncu hayattaysa AI ates eder.
		if (OwnerCharacter && PlayerCharacter && PlayerCharacter->IsAlive) {
			OwnerCharacter->Shoot();
			Result = EBTNodeResult::Succeeded;
		}
	}

	return Result;
}
