// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructableWall.h"


ADestructableWall::ADestructableWall() {
}


/// <summary>
///PARTIE A FAIRE DANS LE SERVEUR
/// </summary>
void ADestructableWall::Destroyed() {
	if (ArrayOfSkills.Num()!=0) {
		ASkills* skill = GetWorld()->SpawnActor<ASkills>(ArrayOfSkills[rand() % ArrayOfSkills.Num() ] , GetActorLocation(), GetActorRotation());
	}

}