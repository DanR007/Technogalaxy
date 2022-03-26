// Copyright Epic Games, Inc. All Rights Reserved.

#include "BruGameMode.h"
#include "BruCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABruGameMode::ABruGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
