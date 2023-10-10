// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/BoxComponent.h"
#include "MyWeapon.h"

// Sets default values
AMyWeapon::AMyWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WAEPON"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> S_Weapon(TEXT("StaticMesh'/Game/STF/Pack03-LandscapePro/Environment/Foliage/BrokenTree/SM_tree_dead.SM_tree_dead'"));

	if (S_Weapon.Succeeded())
	{
		Weapon->SetStaticMesh(S_Weapon.Object);

	}
	Weapon->SetCollisionProfileName(TEXT("NoCollision"));

}

// Called when the game starts or when spawned
void AMyWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


