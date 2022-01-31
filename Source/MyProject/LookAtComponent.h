// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "LookAtComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API ULookAtComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULookAtComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	AActor* TargetActor;
	bool bCanSeeActor = false;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	bool LookAtActor();

	FORCEINLINE void SetTarget(AActor* NewTarget) { TargetActor = NewTarget; }

	FORCEINLINE bool CanSeeActor() { return bCanSeeActor ; }
};
