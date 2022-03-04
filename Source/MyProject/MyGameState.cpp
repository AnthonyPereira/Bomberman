// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameState.h"
#include "MyProjectGameMode.h"

AMyGameState::AMyGameState() : x(1) {
	ready = false;
}

void AMyGameState::OnRep_ReplicatedHasBegunPlay() {
	while (!HasBegunPlay()) {

	}
	AMyProjectGameMode* const MyGameMode = Cast<AMyProjectGameMode>(AuthorityGameMode);
	matrice = MyGameMode->matrice;
	ready = true;
}