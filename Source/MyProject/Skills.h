// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "E_SkillsType.h"

#include "Skills.generated.h"

UCLASS()
class MYPROJECT_API ASkills : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkills();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = VictoryBox, meta = (AllowPrivateAccess = "true"));
	class USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = VictoryBox, meta = (AllowPrivateAccess = "true"));
	class UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere, Category = Skills)
	TEnumAsByte<ESkillsType>  SkillType;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	

protected:

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlapperComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
