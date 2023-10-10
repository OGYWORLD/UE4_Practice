// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MyBTTaskNode_Attack.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API UMyBTTaskNode_Attack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UMyBTTaskNode_Attack();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
