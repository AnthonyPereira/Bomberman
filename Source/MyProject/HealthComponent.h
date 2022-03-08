// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = Health)
	int Health = 2;
	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void LoseHealth(int amount);
	FORCEINLINE int GetHealthPercent() const { return Health ; }

	bool CanTakeDamage=true;
	
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = Health)
	int Health = 1;
	FTimerHandle timer;

	inline void ResetCanTakeDamage() { CanTakeDamage = true; };
		
};
