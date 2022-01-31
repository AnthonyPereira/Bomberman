// Fill out your copyright notice in the Description page of Project Settings.


#include "EscapeFunctionLibrary.h"

#include <Engine/World.h>

#include <DrawDebugHelpers.h>

bool UEscapeFunctionLibrary::CanSeeActor(const UWorld* World, FVector Location, const AActor* TargetActor, TArray<const AActor*> IgnoreActors) {

	if (TargetActor == nullptr) return false;
	FHitResult Hit;

	FVector Start = Location;
	FVector End = TargetActor->GetActorLocation();

	FCollisionQueryParams QueryParam;
	QueryParam.AddIgnoredActors(IgnoreActors);

	ECollisionChannel Channel = ECollisionChannel::ECC_GameTraceChannel1;
	World->LineTraceSingleByChannel(Hit, Start, End, Channel,QueryParam);

	if (!Hit.bBlockingHit) DrawDebugLine(World, Start, End, FColor::Red);

	return !Hit.bBlockingHit;
}
