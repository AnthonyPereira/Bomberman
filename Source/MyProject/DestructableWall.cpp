// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructableWall.h"


ADestructableWall::ADestructableWall() {
}


/// <summary>
///PARTIE A FAIRE DANS LE SERVEUR
/// </summary>
void ADestructableWall::Destroyed() {
	if (ArrayOfSkills.Num()!=0 && rand()%5 <=2) {
		int index = rand() % 10;
		if (index < 4) {
			index = 2;
		}else if (index < 8) {
			index = 1;
		}
		else {
			index = 2;

		}
		if (HasAuthority()) {
			ASkills* skill = GetWorld()->SpawnActor<ASkills>(ArrayOfSkills[index], GetActorLocation(), GetActorRotation());
		}
	}

}