// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "PN1StatManager.h"

// Sets default values for this component's properties
UPN1StatManager::UPN1StatManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bWantsInitializeComponent = true;

}


// Called when the game starts
void UPN1StatManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UPN1StatManager::InitializeComponent()
{
	Super::InitializeComponent();

	SetPlayer1Stat(1);

	//UE_LOG(LogTemp, Log, TEXT("PN1StatManagerCheck!!! %d"), Level);

}


// Called every frame
void UPN1StatManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPN1StatManager::SetPlayer1Stat(int32 RowName)
{
	auto GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance)
	{
		auto EnemyStat = GameInstance->GetMyCharacterData(RowName);
		if (EnemyStat)
		{
			Level = EnemyStat->Level;
			Attack = EnemyStat->Attack;
			SetHP(EnemyStat->MaxHP);
			MaxHP = EnemyStat->MaxHP;
		}
	}
}

void UPN1StatManager::OnAttacked(float DamageAmount)
{
	int32 NewHP = HP - DamageAmount;

	SetHP(NewHP);

	UE_LOG(LogTemp, Log, TEXT("Attacked %d"), HP);
}

void UPN1StatManager::SetHP(int32 NewHP)
{
	HP = NewHP;

	if (HP < 0)
	{
		HP = 0;
	}

	UE_LOG(LogTemp, Log, TEXT("Now HP is %d / %d"), HP, MaxHP);


	OnHpChanged.Broadcast();
}

