// Fill out your copyright notice in the Description page of Project Settings.

#include "BehaviorTree/BlackboardComponent.h"
#include "MyAIController.h"
#include "MyCharacter.h"
#include "MyBTTaskNode_Attack.h"

UMyBTTaskNode_Attack::UMyBTTaskNode_Attack()
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UMyBTTaskNode_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto Default_Character = Cast<AMyCharacter>(OwnerComp.GetAIOwner()->GetPawn());

	if (Default_Character)
	{
		Default_Character->Attack();

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
