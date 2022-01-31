// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Patate.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class MYPROJECT_API AEnemy : public ACharacter
{
	GENERATED_BODY()
		

public:
	// Sets default values for this character's properties
	AEnemy();
	bool bCanSeePlayer;
	bool bPreviousCanSeePlayer;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = LookAt, meta = (AllowPrivateAccess = "true"));
	class ULookAtComponent* LookAtComponent;

	FTimerHandle ThrowTimerHandle;

	float ThrowingInterval = 2.f;
	float ThrowingDelay = 1.f;

	void ThrowPatate();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Patate)
	TSubclassOf<class APatate> PatateClass;


};
