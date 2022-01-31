// Fill out your copyright notice in the Description page of Project Settings.


#include "LookAtComponent.h"
#include <MyProject\EscapeFunctionLibrary.h>
#include <Runtime\Engine\Classes\Kismet\KismetMathLibrary.h>

// Sets default values for this component's properties
ULookAtComponent::ULookAtComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULookAtComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

bool ULookAtComponent::LookAtActor()
{
	const TArray<const AActor*> IgnoreActors = { GetOwner(),TargetActor };

	if (UEscapeFunctionLibrary::CanSeeActor(GetWorld(), GetComponentLocation(), TargetActor, IgnoreActors)) {
		FVector Start = GetOwner()->GetActorLocation();
		FVector End = TargetActor->GetActorLocation();
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(Start, End);
		LookAtRotation.Pitch = 0;
		LookAtRotation.Roll = 0;
		GetOwner()->SetActorRotation(LookAtRotation);
		return true;
	}
	return false;
}


// Called every frame
void ULookAtComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	bCanSeeActor = LookAtActor();

}

