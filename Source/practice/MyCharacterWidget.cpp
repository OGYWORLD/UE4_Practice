// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacterWidget.h"
#include "Components/ProgressBar.h"
#include "PN1StatManager.h"

void UMyCharacterWidget::UpdateHP()
{
	if (CurrentStatComp.IsValid())
	{
		PB_HpBar->SetPercent(CurrentStatComp->GetHPRatio());
	}
}

void UMyCharacterWidget::BindHP(UPN1StatManager* StatManager)
{
	UE_LOG(LogTemp, Log, TEXT("Delegate Binding Check"));
	
	CurrentStatComp = StatManager;

	StatManager->OnHpChanged.AddUObject(this, &UMyCharacterWidget::UpdateHP);
}
