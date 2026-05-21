// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTService_PlayerLocation.h"

#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"


UMyBTService_PlayerLocation::UMyBTService_PlayerLocation()
{
	// Behavior Tree editor'unde service bu isimle gorunur.
	NodeName = TEXT("Get Player Location");
}

void UMyBTService_PlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	if (PlayerPawn && Blackboard)
	{
		// Service'te secilen blackboard key'i hangi hedef degerin guncellenecegini belirler.
		Blackboard->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
	}
}
