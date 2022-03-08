// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <MyProject\E_SkillsType.h>

#include "Character_Skill.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UCharacter_Skill : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacter_Skill();
	UCharacter_Skill(int value, int max);


	void Init(int v,int m, TEnumAsByte<ESkillsType> s);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(BlueprintReadWrite,EditAnyWhere, Category = Skills)
	int value = 0;

	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = Skills)
	int max = 0;

	TEnumAsByte<ESkillsType>  SkillType ;

	bool increase();

	bool decrease();

};
