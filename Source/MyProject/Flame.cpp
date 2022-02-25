// Fill out your copyright notice in the Description page of Project Settings.


#include "Flame.h"
#include <Components/BoxComponent.h>
#include <MyProject\MyProjectCharacter.h>
#include <MyProject\MyProjectCharacter.h>


// Sets default values
AFlame::AFlame()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetBoxExtent(FVector(30.f, 30.f, 20.f));
	CollisionBox->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AFlame::OnBeginOverlap);
}

// Called when the game starts or when spawned
void AFlame::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(1.f);
	
}

void AFlame::OnBeginOverlap(UPrimitiveComponent* OverlapperComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){	
	AMyProjectCharacter* Player = Cast<AMyProjectCharacter>(OtherActor);
	if (Player != nullptr) {
		UHealthComponent* HealthComponent = Player->FindComponentByClass<UHealthComponent>();
		HealthComponent->LoseHealth(1.f);
	}
}


