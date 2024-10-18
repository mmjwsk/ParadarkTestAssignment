// Copyright Epic Games, Inc. All Rights Reserved.

#include "Majewski_TestTaskGameMode.h"
#include "Majewski_TestTaskCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMajewski_TestTaskGameMode::AMajewski_TestTaskGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
