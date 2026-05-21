// Fill out your copyright notice in the Description page of Project Settings.
#include "BTService_PlayerLocationIfSeen.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h" 

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
	// Behavior Tree editor'unde service bu isimle gorunur.
	NodeName = TEXT("Update Player Location If Seen");
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	AAIController* AIOwner = OwnerComp.GetAIOwner();

	if (PlayerPawn && AIOwner)
	{
		// AI oyuncuyu dogrudan gorebiliyorsa hedef konumu blackboard'a yazilir.
		if (AIOwner->LineOfSightTo(PlayerPawn))
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());

			UE_LOG(LogTemp, Warning, TEXT("AI oyuncuyu gordu! Hedefe gidiliyor..."));
		}
		else
		{
			// Gorus kaybolursa hedef konum temizlenir; BT baska dala gecebilir.
			OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
		}
	}
}
