// Fill out your copyright notice in the Description page of Project Settings.

#include "BehaviorTree/BlackBoardComponent.h"
#include "NavigationSystem.h"
#include "MyAIController.h"
#include "MyBTTask_FindPatrolPos.h"

UMyBTTask_FindPatrolPos::UMyBTTask_FindPatrolPos()
{
	NodeName = TEXT("FindPatrolPos");
}

EBTNodeResult::Type UMyBTTask_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	auto CurrentPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (CurrentPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	UNavigationSystemV1* Nav = UNavigationSystemV1::GetNavigationSystem(GetWorld());

	if (Nav == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	FNavLocation RandomLocation;

	if (Nav->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.f, RandomLocation))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName(TEXT("PatrolPos")), RandomLocation.Location);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Type();
}
