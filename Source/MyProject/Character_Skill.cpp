// Fill out your copyright notice in the Description page of Project Settings.


#include "Character_Skill.h"
#include <MyProject\E_SkillsType.h>
#include "MyInterface.h"



UCharacter_Skill::UCharacter_Skill() 
{
	
	PrimaryComponentTick.bCanEverTick = false;

}


// Sets default values for this component's properties
void UCharacter_Skill::Init(int v, int m, TEnumAsByte<ESkillsType> s) 
{
	
	this->value = v;
	this->max = m;
	this->SkillType = s;
}


// Called when the game starts
void UCharacter_Skill::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UCharacter_Skill::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

bool UCharacter_Skill::increase() {
	if (GetOwner()->Implements<UMyInterface>() && value < max) {
		value++;
		IMyInterface::Execute_OnSpeedUpdate(GetOwner());
		IMyInterface::Execute_OnMeshUpdate(GetOwner());

		return true;
	}
	return false;
}

bool UCharacter_Skill::decrease() {
	if (GetOwner()->Implements<UMyInterface>() && value > 0) {
		value--;
		IMyInterface::Execute_OnSpeedUpdate(GetOwner());
		IMyInterface::Execute_OnMeshUpdate(GetOwner());

		return true;
	}
	return false;
}