// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructableWall.h"


ADestructableWall::ADestructableWall() {
}


/// <summary>
///PARTIE A FAIRE DANS LE SERVEUR
/// </summary>
void ADestructableWall::Destroyed() {
	if (ArrayOfSkills.Num()!=0 && rand()%5 <=2) {
		int index = rand() % 20;
		if (index < 8) {
			index = 0;
		}else if (index < 14) {
			index = 1;
		}else if (index < 19) {
			index = 2;
		}
		else {
			index = 3;

		}
		if (HasAuthority()) {
			ASkills* skill = GetWorld()->SpawnActor<ASkills>(ArrayOfSkills[index], GetActorLocation(), GetActorRotation());
		}
	}

}