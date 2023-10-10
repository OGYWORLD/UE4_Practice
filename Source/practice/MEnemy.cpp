// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacterWidget.h"
#include "Components/WidgetComponent.h"
#include "PN1StatManager.h"
#include "MEnemy.h"

// Sets default values
AMEnemy::AMEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("SkeletalMesh'/Game/ParagonRevenant/Characters/Heroes/Revenant/Meshes/Revenant.Revenant'"));

	if (SM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM.Object);
	}

	Stat = CreateDefaultSubobject<UPN1StatManager>(TEXT("STAT"));

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));
	
	HpBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBAR"));

	HpBar->SetupAttachment(GetMesh());

	HpBar->SetRelativeLocation(FVector(0.f, 0.f, 200.f));

	HpBar->SetWidgetSpace(EWidgetSpace::Screen);

	static ConstructorHelpers::FClassFinder<UUserWidget> UW(TEXT("WidgetBlueprint'/Game/UI/WB_HPBar.WB_HPBar_C'"));

	if (UW.Succeeded())
	{
		HpBar->SetWidgetClass(UW.Class);
		HpBar->SetDrawSize(FVector2D(200.f, 50.f));
	}
}

// Called when the game starts or when spawned
void AMEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMEnemy::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	HpBar->InitWidget();

	auto Widget = Cast<UMyCharacterWidget>(HpBar->GetUserWidgetObject());
	if (Widget)
	{
		Widget->BindHP(Stat);
	}
}

// Called every frame
void AMEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AMEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	//UE_LOG(LogTemp, Log, TEXT("TakeDamage is Working?"));
	Stat->OnAttacked(DamageAmount);

	return DamageAmount;
}