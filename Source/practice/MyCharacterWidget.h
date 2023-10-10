// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyCharacterWidget.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API UMyCharacterWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_HpBar;

	TWeakObjectPtr<class UPN1StatManager> CurrentStatComp;

public:
	void UpdateHP();

	void BindHP(class UPN1StatManager* StatManager);
};
