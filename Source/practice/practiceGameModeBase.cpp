// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyCharacter.h"
#include "practiceGameModeBase.h"

ApracticeGameModeBase::ApracticeGameModeBase()
{
	static ConstructorHelpers::FClassFinder<AMyCharacter> BP_Char(TEXT("Blueprint'/Game/BluePrints/BP_Character.BP_Character_C'"));

	if (BP_Char.Succeeded())
	{
		DefaultPawnClass = BP_Char.Class;
	}
}