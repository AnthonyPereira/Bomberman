// Fill out your copyright notice in the Description page of Project Settings.


#include "SceneBuilder.h"
#include "MyGameState.h"
#include "MyProjectGameMode.h"

// Sets default values
ASceneBuilder::ASceneBuilder()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASceneBuilder::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority()) {

		LoadLevel();
		if (WallClass == nullptr || ExternWallClass == nullptr || DestroyWallClass == nullptr) {
			return;
		}

		FRotator ForwardVector(0.f, 0.f, 0.f);
		FTransform SpawnTransform(ForwardVector);
		if (HasAuthority()) {
			GetWorld()->SpawnActor<AWall>(ExternWallClass, FTransform(FRotator(0.f, 90.f, 0.f), FVector(0, -(W / 2 + 1) * 100.f, 50), FVector(1, H + 2, 1.5)));
			GetWorld()->SpawnActor<AWall>(ExternWallClass, FTransform(FRotator(0.f, 90.f, 0.f), FVector(0, (W / 2 + 1) * 100.f, 50), FVector(1, H + 2, 1.5)));
			GetWorld()->SpawnActor<AWall>(ExternWallClass, FTransform(ForwardVector, FVector(-(H / 2 + 1) * 100.f, 0, 50), FVector(1, W, 1.5)));
			GetWorld()->SpawnActor<AWall>(ExternWallClass, FTransform(ForwardVector, FVector((H / 2 + 1) * 100.f, 0, 50), FVector(1, W, 1.5)));

			GetWorld()->SpawnActor<AWall>(GroundClass, FTransform(ForwardVector, FVector(0.f, 0.f, -15), FVector(H, W, 1)));

			float x_offset = (-H / 2) * 100.f;
			float y_offset = (-W / 2) * 100.f;
			SpawnTransform.SetRotation(FRotator(0.f, 90.f, 0.f).Quaternion());

			for (int i = 0; i < H; ++i) {
				for (int j = 0; j < W; ++j) {
					if (matrice[i][j] == 1) {
						SpawnTransform.SetLocation(FVector(x_offset + i * 100.f, y_offset + j * 100.f, 70));
						GetWorld()->SpawnActor<AWall>(WallClass, SpawnTransform);
					}
					if (matrice[i][j] == 2) {
						SpawnTransform.SetLocation(FVector(x_offset + i * 100.f, y_offset + j * 100.f, 45));
						GetWorld()->SpawnActor<AWall>(DestroyWallClass, SpawnTransform);
					}
				}
			}
		}
	}
}

// Called every frame
void ASceneBuilder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ASceneBuilder::LoadLevel() {
	for (int i = 0; i < H; ++i) {
		TArray<int> line;
		for (int j = 0; j < W; ++j) {
			if ((i == 0 && j == 0) || (i == H - 1 && j == W - 1) || (i == 0 && j == W - 1) || (i == H - 1 && j == 0) ||
				(i == 1 && j == 0) || (i == H - 2 && j == W - 1) || (i == 0 && j == W - 2) || (i == H - 1 && j == 1) ||
				(i == 0 && j == 1) || (i == H - 1 && j == W - 2) || (i == 1 && j == W - 1) || (i == H - 2 && j == 0)
				)
			{
				line.Add(0);
				//Spawn ici

			}
			else if ((i % 2 != 0 && j % 2 != 0)) {
				line.Add(1);
			}
			else if ((i == 2 && j == 0) || (i == H - 3 && j == W - 1) || (i == 0 && j == W - 3) || (i == H - 1 && j == 2) ||
				(i == 0 && j == 2) || (i == H - 1 && j == W - 3) || (i == 2 && j == W - 1) || (i == H - 3 && j == 0) || (rand() % 11 < 7)) {
				line.Add(2);
			}
			else {
				line.Add(0);
			}
		}
		matrice.Add(line);
	}
}

