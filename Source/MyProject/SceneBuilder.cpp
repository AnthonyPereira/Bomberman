// Fill out your copyright notice in the Description page of Project Settings.


#include "SceneBuilder.h"

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
	if (WallClass == nullptr || ExternWallClass == nullptr || DestroyWallClass ==nullptr) {
		return;
	}
	FRotator ForwardVector(0.f, 0.f, 0.f);
	FTransform SpawnTransform(ForwardVector);
	
	GetWorld()->SpawnActor<AWall>(ExternWallClass,FTransform(ForwardVector,FVector((-H * 100.f) + H / 2 * 200.f, (1 - W) * 100.f, 50), FVector((H *2)-1, 1, 1.75)));
	GetWorld()->SpawnActor<AWall>(ExternWallClass,FTransform(ForwardVector,FVector((-H * 100.f) + H / 2 * 200.f, ((1 - W) * 100.f) + (W-1) * 200.f, 50), FVector((H * 2) - 1, 1, 1.75)));
	GetWorld()->SpawnActor<AWall>(ExternWallClass,FTransform(ForwardVector,FVector((1-H) * 100.f, (- W * 100.f) + W / 2 * 200.f, 50), FVector(1, (W * 2) - 1, 1.75)));
	GetWorld()->SpawnActor<AWall>(ExternWallClass, FTransform(ForwardVector, FVector(((H-1) * 100.f) , ((-W) * 100.f) + W / 2 * 200.f, 50), FVector(1, (W * 2) - 1, 1.75)));

	GetWorld()->SpawnActor<AWall>(GroundClass, FTransform(ForwardVector, FVector(0.f,0.f, -15), FVector(H*2-1,W*2-1, 1)));


	float x_offset = (3 - H) * 100.f;
	float y_offset = (3 - W) * 100.f;

	for (int i = 0; i < W-2; ++i) {
		for (int j = 0; j < H-2; ++j) {			
			SpawnTransform.SetLocation(FVector(x_offset + j * 200.f, y_offset + i * 200.f, 50));
			GetWorld()->SpawnActor<AWall>(WallClass, SpawnTransform);
		}
	}
	
}

// Called every frame
void ASceneBuilder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

