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
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/ThirdPersonCharacter.ThirdPersonCharacter_C"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

int AMyProjectGameMode::GetX() const{
	return GetGameState<AMyGameState>()->x;
}

void AMyProjectGameMode::SetX(int newX){
	GetGameState<AMyGameState>()->x = newX;
}

void AMyProjectGameMode::StartPlay() {
	GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::FString("StartPlay"));
	StartPlayEvent();
	Super::StartPlay();
}

void AMyProjectGameMode::StartPlayEvent_Implementation(){
	for (int i = 0; i < H; ++i) {
		TArray<int> line;
		for (int j = 0; j < W; ++j) {
			if ((i == 0 && j == 0) || (i == H - 1 && j == W - 1) || (i == 0 && j == W - 1) || (i == H - 1 && j == 0) ||
				(i == 1 && j == 0) || (i == H - 2 && j == W - 1) || (i == 0 && j == W - 2) || (i == H - 1 && j == 1) ||
				(i == 0 && j == 1) || (i == H - 1 && j == W - 2) || (i == 1 && j == W - 1) || (i == H - 2 && j == 0)
				)
			{
				line.Add(0);
				//Spawn ici

			}
			else if ((i % 2 != 0 && j % 2 != 0)) {
				line.Add(1);
			}
			else if ((i == 2 && j == 0) || (i == H - 3 && j == W - 1) || (i == 0 && j == W - 3) || (i == H - 1 && j == 2) ||
				(i == 0 && j == 2) || (i == H - 1 && j == W - 3) || (i == 2 && j == W - 1) || (i == H - 3 && j == 0) || (rand() % 11 < 7)) {
				line.Add(2);
			}
			else {
				line.Add(0);
			}
		}
		matrice.Add(line);
	}


	AMyGameState* MyGameState = GetGameState<AMyGameState>();
	GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::FString("matrix go game state"));
	if (MyGameState == nullptr) {
		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::FString("ret null"));
		return;
	}
		
	MyGameState->matrice = matrice;
}