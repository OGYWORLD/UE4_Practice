// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyAIController.h"
#include "MyBTDecorator_CanAttack.h"

UMyBTDecorator_CanAttack::UMyBTDecorator_CanAttack()
{
	NodeName = TEXT("CanAttack");
}

bool UMyBTDecorator_CanAttack::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto Me = Cast<AMyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (Me == nullptr) return false;

	auto Player = Cast<AMyCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("Target"))));
	if (Player == nullptr) return false;


	return bResult && Player->GetDistanceTo(Me) <= 100.f;
	//return bResult && Me->GetDistanceTo(Player) <= 200.f;
	

	return false;
}

