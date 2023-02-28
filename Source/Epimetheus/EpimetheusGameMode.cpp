// Copyright Epic Games, Inc. All Rights Reserved.

#include "EpimetheusGameMode.h"
#include "EpimetheusCharacter.h"
#include "UObject/ConstructorHelpers.h"

AEpimetheusGameMode::AEpimetheusGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
