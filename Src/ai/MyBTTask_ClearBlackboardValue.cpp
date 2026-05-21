// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_ClearBlackboardValue.h"
#include "BehaviorTree/BlackboardComponent.h"


UMyBTTask_ClearBlackboardValue::UMyBTTask_ClearBlackboardValue()
{
	// Behavior Tree editor'unde node bu isimle gorunur.
	NodeName = TEXT("Clear Blackboard Value");
}

EBTNodeResult::Type UMyBTTask_ClearBlackboardValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard) {
		// Task uzerinde secilen blackboard key'i temizlenir.
		Blackboard->ClearValue(GetSelectedBlackboardKey());
	}
	return EBTNodeResult::Succeeded;
}


