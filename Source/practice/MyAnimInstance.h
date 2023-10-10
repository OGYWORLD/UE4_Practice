// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PawnMovementComponent.h"
#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"
DECLARE_MULTICAST_DELEGATE(FAttackCheck);

/**
 * 
 */
UCLASS()
class PRACTICE_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:

	UMyAnimInstance();

	void PlayAttackMontage();

	void PlayDJMontage();

	UFUNCTION()
	void AnimNotify_AttackHit();

	FAttackCheck AttackCheck;

	FName ReturnMontageFName(int32 index);

	void MakeJumpToMontageSection(FName MontageSectionName);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player, Meta = (AllowPrivateAccess))
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player, Meta = (AllowPrivateAccess))
	bool IsFalling;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player, Meta = (AllowPrivateAccess))
	UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player, Meta = (AllowPrivateAccess))
	UAnimMontage* DoubleJumpMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player, Meta = (AllowPrivateAccess))
	float Horizontal;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player, Meta = (AllowPrivateAccess))
	float Vertical;
};
