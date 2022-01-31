// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomb.h"
#include <Components/SphereComponent.h>

// Sets default values
ABomb::ABomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("BOMB"));
	SphereComponent->SetSphereRadius(40.f);
	//SphereComponent->SetCollisionProfileName(FName("Patatepreset"));
	SphereComponent->SetSimulatePhysics(true);
	SphereComponent->SetNotifyRigidBodyCollision(true);
	//SphereComponent->OnComponentHit.AddDynamic(this, &APatate::OnHit);
	RootComponent = SphereComponent;
}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(5.f);
}

// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

