// Copyright Epic Games, Inc. All Rights Reserved.

#include "Lesson4GameMode.h"
#include "Lesson4Character.h"
#include "UObject/ConstructorHelpers.h"

ALesson4GameMode::ALesson4GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
