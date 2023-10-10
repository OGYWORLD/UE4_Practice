// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PN1StatManager.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpChanged);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PRACTICE_API UPN1StatManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPN1StatManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected:
	virtual void InitializeComponent() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void SetPlayer1Stat(int32 RowName);

public:
	void OnAttacked(float DamageAmount);

public:
	int32 GetPlayerNumber()
	{
		return PlayerNumber;
	}

	int32 GetLevel()
	{
		return Level;
	}

	int32 GetAttack()
	{
		return Attack;
	}

	int32 GetHP()
	{
		return HP;
	}

	int32 GetMaxHP()
	{
		return MaxHP;
	}

	float GetHPRatio()
	{
		return (float)HP / (float)MaxHP;
	}

	void SetHP(int32 NewHP);

	FOnHpChanged OnHpChanged;

private:
	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 PlayerNumber;

	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Level;

	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Attack;

	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 HP;

	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 MaxHP;
		
};
