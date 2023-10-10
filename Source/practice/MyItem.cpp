// Fill out your copyright notice in the Description page of Project Settings.

#include "MyItem.h"

// Sets default values
AMyItem::AMyItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Item = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ITEM"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> S_Item(TEXT("StaticMesh'/Game/STF/Pack03-LandscapePro/Environment/Foliage/Grass/SM_GrassGroup03.SM_GrassGroup03'"));

	if (S_Item.Succeeded())
	{
		Item->SetStaticMesh(S_Item.Object);
	}

	Item->SetCollisionProfileName(TEXT("MyCollectible"));

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));

	Item->SetupAttachment(RootComponent);

	Trigger->SetupAttachment(Item);

	Trigger->SetCollisionProfileName(TEXT("MyCollectible"));

	Trigger->SetBoxExtent(FVector(30.f, 30.f, 30.f));

}

// Called when the game starts or when spawned
void AMyItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyItem::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AMyItem::OnCharacterOverlap);
}

void AMyItem::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SerrpResult)
{
	UE_LOG(LogTemp, Log, TEXT("Overlapped"));

	AMyCharacter* MyCharacter = Cast<AMyCharacter>(OtherActor);

	if (MyCharacter)
	{
		FName HeadItem(TEXT("HeadItem"));

		AttachToComponent(MyCharacter->GetMesh(),
			FAttachmentTransformRules::SnapToTargetNotIncludingScale,
			HeadItem);
	}
}

