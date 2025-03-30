// Copyright Epic Games, Inc. All Rights Reserved.

#include "MovanLabGameMode.h"
#include "MovanLabCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMovanLabGameMode::AMovanLabGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
