// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API UMyHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (bindWidget))
	class UTextBlock* AmmoText;
	
};
