// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "MyBTService_SearchTarget.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API UMyBTService_SearchTarget : public UBTService
{
	GENERATED_BODY()

public:
	UMyBTService_SearchTarget();
	
public:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
