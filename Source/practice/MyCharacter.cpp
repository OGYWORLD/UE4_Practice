// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/WidgetComponent.h"
#include "MyCharacterWidget.h"
#include "PN1StatManager.h"
#include "MyItem.h"
#include "MyWeapon.h"
#include "MyAnimInstance.h"
#include "DrawDebugHelpers.h"
#include "MyCharacter.h"
#include "MyAIController.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Player(TEXT("SkeletalMesh'/Game/ParagonSerath/Characters/Heroes/Serath/Meshes/Serath.Serath'"));

	if (Player.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(Player.Object);
	}

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	SpringArm->TargetArmLength = 500.f;
	SpringArm->SetRelativeRotation(FRotator(-35.f, 0.f, 0.f));

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));

	Stat = CreateDefaultSubobject<UPN1StatManager>(TEXT("STAT"));

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

	// Pawn을 AI로 사용할 때 실행되는 클래스
	AIControllerClass = AMyAIController::StaticClass();

	// 월드에 배치된 Pawn을 AI로 지정
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	AMyWeapon* Weapon = GetWorld()->SpawnActor<AMyWeapon>(FVector(0.f, 90.f, 50.f), FRotator::ZeroRotator);
	
	AMyItem* Item = GetWorld()->SpawnActor<AMyItem>(FVector(0.f, 50.f, 50.f), FRotator::ZeroRotator);

	FName RightWeapon(TEXT("RightWeapon"));

	if (GetMesh()->DoesSocketExist(RightWeapon) && Weapon)
	{
		Weapon->AttachToComponent(GetMesh(),
			FAttachmentTransformRules::SnapToTargetNotIncludingScale,
			RightWeapon);
		
	}
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AMyCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("RightLeft"), this, &AMyCharacter::RightLeft);
	
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AMyCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("DoubleJump"), EInputEvent::IE_DoubleClick, this, &AMyCharacter::DoubleJump);

	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AMyCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AMyCharacter::AddControllerPitchInput);
	
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &AMyCharacter::Attack);
}

void AMyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();


	Anim = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());

	if (Anim)
	{
		Anim->OnMontageEnded.AddDynamic(this, &AMyCharacter::OnAttackMontageEnded);
		Anim->AttackCheck.AddUObject(this, &AMyCharacter::AttackCheck);
	}

	HpBar->InitWidget();

	auto Widget = Cast<UMyCharacterWidget>(HpBar->GetUserWidgetObject());

	if (Widget)
	{
		Widget->BindHP(Stat);
		UE_LOG(LogTemp, Log, TEXT("Initialiizeefsfef"));
	}
}



void AMyCharacter::UpDown(float Value)
{
	if (Value == 0.f) return;

	AddMovementInput(GetActorForwardVector(), Value);

	//UE_LOG(LogTemp, Log, TEXT("%s"), *GetActorLocation().ToString());

	Vertical = Value;
}

void AMyCharacter::RightLeft(float Value)
{
	if (Value == 0.f) return;

	AddMovementInput(GetActorRightVector(), Value);
	Horizontal = Value;

}

void AMyCharacter::Attack()
{
	if (IsAttacking) return;

	IsAttacking = true;

	index = (index + 1) % 2;

	auto MyAnimInstance = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());

	if (IsValid(MyAnimInstance))
	{
		MyAnimInstance->MakeJumpToMontageSection(MyAnimInstance->ReturnMontageFName(index));

		MyAnimInstance->PlayAttackMontage();
	}
}

void AMyCharacter::DoubleJump()
{
	auto MyAnimInstance = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());

	if (IsValid(MyAnimInstance))
	{
		MyAnimInstance->PlayDJMontage();
	}
}

void AMyCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool binterrupt)
{
	IsAttacking = false;
	UE_LOG(LogTemp, Warning, TEXT("OnAttackMontageEnded is working"));
}

void AMyCharacter::AttackCheck()
{
	//FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);

	float AttackRange = 100.f;
	float AttackRadius = 50.f;

	bResult = GetWorld()->SweepSingleByChannel(
		OUT HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * AttackRange, // 충돌인정범위
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(AttackRadius),
		Params
		);

	FVector AttackDetect = GetActorForwardVector() * AttackRange;
	FVector Center = GetActorLocation() + AttackDetect * 0.5;
	float HalfHeight = AttackRange * 0.5 + AttackRadius;

	FQuat Rotation = FRotationMatrix::MakeFromY(AttackDetect).ToQuat();
	FColor DrawColor;

	if (bResult)
	{
		DrawColor = FColor::Green;
	}
	else
	{
		DrawColor = FColor::Red;

	}

	DrawDebugCapsule(GetWorld(), Center, HalfHeight, AttackRadius, Rotation, DrawColor, false, 2.f);

	if (bResult && HitResult.Actor.IsValid())
	{
		FDamageEvent DamageEvent;

		HitResult.Actor->TakeDamage(Stat->GetAttack(), DamageEvent, GetController(), this);

		UE_LOG(LogTemp, Log, TEXT("MyCharacter1 Attack to %s"), *HitResult.Actor->GetName());
	}
}

float AMyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Stat->OnAttacked(DamageAmount);

	return DamageAmount;
}

