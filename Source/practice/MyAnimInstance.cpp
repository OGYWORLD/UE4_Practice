// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"
#include "MyAnimInstance.h"

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();

	if (IsValid(Pawn))
	{
		Speed = Pawn->GetVelocity().Size();
	}

	auto Character = Cast<AMyCharacter>(Pawn);

	if (Character)
	{
		IsFalling = Character->GetMovementComponent()->IsFalling();
		Horizontal = Character->Horizontal;
		Vertical = Character->Vertical;
	}
}

UMyAnimInstance::UMyAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> M_Attack(TEXT("AnimMontage'/Game/Montage/Serath_Skeleton_Montage.Serath_Skeleton_Montage'"));

	if (M_Attack.Succeeded())
	{
		AttackMontage = M_Attack.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> M_DoubleJump(TEXT("AnimMontage'/Game/Montage/DoubleJump_Montage.DoubleJump_Montage'"));

	if (M_DoubleJump.Succeeded())
	{
		DoubleJumpMontage = M_DoubleJump.Object;
	}
}

void UMyAnimInstance::PlayAttackMontage()
{
	if (!Montage_IsPlaying(DoubleJumpMontage)) Montage_Play(AttackMontage);
}

void UMyAnimInstance::PlayDJMontage()
{
	if(!Montage_IsPlaying(AttackMontage)) Montage_Play(DoubleJumpMontage);
}

void UMyAnimInstance::AnimNotify_AttackHit()
{
	UE_LOG(LogTemp, Log, TEXT("NotiNoti"));
	AttackCheck.Broadcast();
}

FName UMyAnimInstance::ReturnMontageFName(int32 index)
{
	return FName(FString::Printf(TEXT("AttackHit%d")), index);
}

void UMyAnimInstance::MakeJumpToMontageSection(FName MontageSectionName)
{
	Montage_JumpToSection(MontageSectionName, AttackMontage);
}


