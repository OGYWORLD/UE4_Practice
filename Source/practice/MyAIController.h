// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API AMyAIController : public AAIController
{
	GENERATED_BODY()

	AMyAIController();

public:
	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnUnPossess() override;

private:
	void RandomMove();

	FTimerHandle TimerHandle;

	UPROPERTY()
	class UBehaviorTree* BehaviorTree;

	UPROPERTY()
	class UBlackboardData* BlackboardData;
	
};
