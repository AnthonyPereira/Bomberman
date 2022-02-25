// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Wall.h"
#include "Skills.h"

#include "DestructableWall.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API ADestructableWall : public AWall
{
	GENERATED_BODY()

	ADestructableWall();


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skills)
	TArray<TSubclassOf<ASkills>> ArrayOfSkills;

	virtual void Destroyed() override;

};
