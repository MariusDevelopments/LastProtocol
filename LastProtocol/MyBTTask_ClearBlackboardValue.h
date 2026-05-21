// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MyBTTask_ClearBlackboardValue.generated.h"

/** Secili blackboard degerini temizleyen yardimci Behavior Tree task'i. */
UCLASS()
class LASTPROTOCOL_API UMyBTTask_ClearBlackboardValue : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	// Editor'de gorunecek task ismi constructor icinde verilir.
	UMyBTTask_ClearBlackboardValue();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
