// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MyBTTask_FindPatrolPos.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API UMyBTTask_FindPatrolPos : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UMyBTTask_FindPatrolPos();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	

};
