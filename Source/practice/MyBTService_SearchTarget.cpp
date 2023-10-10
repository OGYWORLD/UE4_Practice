// Fill out your copyright notice in the Description page of Project Settings.

#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
#include "MyCharacter.h"
#include "MyAIController.h"
#include "MyBTService_SearchTarget.h"

UMyBTService_SearchTarget::UMyBTService_SearchTarget()
{
	NodeName = TEXT("SearchTarget");

	Interval = 1.0f;
}

void UMyBTService_SearchTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto CurrentPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (CurrentPawn == nullptr) return;

	UWorld* World = CurrentPawn->GetWorld();

	if (World == nullptr) return;

	FVector Center = CurrentPawn->GetActorLocation();

	float SearchRadius = 500.f;

	TArray <FOverlapResult> OverlapResult;

	FCollisionQueryParams QueryParams(NAME_None, false, CurrentPawn);

	bool bResult = World->OverlapMultiByChannel(
		OverlapResult,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(SearchRadius),
		QueryParams
	);

	if (bResult)
	{
		for (auto& OverlapResult_Actor : OverlapResult)
		{
			AMyCharacter* PickActor = Cast<AMyCharacter>(OverlapResult_Actor.GetActor());

			if (PickActor && PickActor->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), PickActor);

				DrawDebugSphere(World, Center, SearchRadius, 16, FColor::Green, false, 0.2f);

				return;
			}
		}
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), nullptr);

		DrawDebugSphere(World, Center, SearchRadius, 16, FColor::Red, false, 0.2f);
	}


}
