// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MyGameState.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AMyGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	
	AMyGameState();
	virtual ~AMyGameState() = default;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int x;

	TArray<TArray<int>> matrice;
	bool ready;

	virtual void OnRep_ReplicatedHasBegunPlay();
};
