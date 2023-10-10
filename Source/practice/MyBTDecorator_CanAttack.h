// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "MyBTDecorator_CanAttack.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API UMyBTDecorator_CanAttack : public UBTDecorator
{
	GENERATED_BODY()

public:
	UMyBTDecorator_CanAttack();

public:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
