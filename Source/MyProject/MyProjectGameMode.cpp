// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyProjectGameMode.h"
#include "MyProjectCharacter.h"
#include "MyGameState.h"
#include "MyProjectPlayerController.h"

#include "UObject/ConstructorHelpers.h"

AMyProjectGameMode::AMyProjectGameMode()
{

	GameStateClass = AMyGameState::StaticClass();
	PlayerControllerClass = AMyProjectPlayerController::StaticClass();
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_PlayerCharacter.BP_PlayerCharacter_C"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}