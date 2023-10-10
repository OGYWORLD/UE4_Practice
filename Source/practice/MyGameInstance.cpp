// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

UMyGameInstance::UMyGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> BasicData(TEXT("DataTable'/Game/Data/DT_PlayerStat.DT_PlayerStat'"));

	if (BasicData.Succeeded())
	{
		MyStats = BasicData.Object;
	}
}

void UMyGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Warning, TEXT("MyGameInstance %d"), GetMyCharacterData(1)->Attack);
}

FMyCharacterData* UMyGameInstance::GetMyCharacterData(int32 RowName)
{
	return MyStats->FindRow<FMyCharacterData>(*FString::FromInt(RowName), TEXT(""));
}


