// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Wall.h"
#include "GameFramework/Actor.h"
#include "SceneBuilder.generated.h"

UCLASS()
class MYPROJECT_API ASceneBuilder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASceneBuilder();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Wall);
	int H;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Wall);
	int W;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Wall)
	TSubclassOf<class AWall> WallClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Wall)
	TSubclassOf<class AWall> DestroyWallClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Wall)
	TSubclassOf<class AWall> ExternWallClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Wall)
	TSubclassOf<class AWall> GroundClass;
};
