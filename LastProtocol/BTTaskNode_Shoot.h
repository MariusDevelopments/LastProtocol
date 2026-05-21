// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_Shoot.generated.h"

/**
 * Behavior Tree task'i: AI uygun durumdayken silahini atesler.
 */
UCLASS()
class LASTPROTOCOL_API UBTTaskNode_Shoot : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	// Editor'de gorunecek task ismi constructor icinde verilir.
	UBTTaskNode_Shoot();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
