// Copyright Epic Games, Inc. All Rights Reserved.

#include "Lesson1GameMode.h"
#include "Lesson1Character.h"
#include "UObject/ConstructorHelpers.h"

ALesson1GameMode::ALesson1GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
