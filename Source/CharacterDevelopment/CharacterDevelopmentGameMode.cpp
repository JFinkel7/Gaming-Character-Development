// Copyright Epic Games, Inc. All Rights Reserved.

#include "CharacterDevelopmentGameMode.h"
#include "CharacterDevelopmentCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACharacterDevelopmentGameMode::ACharacterDevelopmentGameMode(){
	// set default pawn class to our Blueprinted character
	// (Game) = Content Folder 
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Character_Box/Blueprints/Blueprint_Character"));
	if (PlayerPawnBPClass.Class != NULL)	
		DefaultPawnClass = PlayerPawnBPClass.Class;
	
}
