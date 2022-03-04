// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyProjectPlayerController.h"
#include "MyProjectGameMode.generated.h"

UCLASS(minimalapi)
class AMyProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMyProjectGameMode();
	virtual ~AMyProjectGameMode() = default;

	TArray<TArray<int>> matrice;
	int H = 11;
	int W = 11;

	UFUNCTION(BlueprintPure, Category = "x")
	virtual int GetX() const;

	UFUNCTION(BlueprintCallable, Category = "x")
		virtual void SetX(int newX);

	virtual void StartPlay();

	UFUNCTION(BlueprintNativeEvent, Category = "x", DisplayName = "Start Play")
		void StartPlayEvent();

	virtual void GenericPlayerInitialization(AController* C);
	
};



