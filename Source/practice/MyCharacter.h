// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/FloatingPawnMovement.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class PRACTICE_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PostInitializeComponents() override;

	void UpDown(float Value);
	void RightLeft(float Value);
	void Attack();
	void DoubleJump();

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Anim, bool binterrupt);

	UFUNCTION()
	void AttackCheck();

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:
	UPROPERTY()
	UCameraComponent* Camera;

	UPROPERTY()
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	UFloatingPawnMovement* Movement;

	UPROPERTY(VisibleAnywhere)
	bool IsAttacking = false;
	
	UPROPERTY(VisibleAnywhere)
	class UMyAnimInstance* Anim;

	UPROPERTY(VisibleAnywhere)
	int32 index = 0;

public:
	UPROPERTY()
	float Horizontal;

	UPROPERTY()
	float Vertical;

private:
	UPROPERTY(VisibleAnywhere)
	class UPN1StatManager* Stat;

public:
	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* HpBar;

public:
	bool bResult;
	FHitResult HitResult;
};
