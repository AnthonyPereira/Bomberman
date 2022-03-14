// Fill out your copyright notice in the Description page of Project Settings.


#include "Skills.h"
#include <Components/BoxComponent.h>

#include <MyProject\MyProjectCharacter.h>

#include <Kismet/KismetSystemLibrary.h>
#include <MyProject\Character_Skill.h>

// Sets default values
ASkills::ASkills()
{
	bReplicates = true;
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bCanEverTick = true;
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = RootScene;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetBoxExtent(FVector(10.f, 10.f, 10.f));
	CollisionBox->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ASkills::OnBeginOverlap);
}

// Called when the game starts or when spawned
void ASkills::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void ASkills::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASkills::OnBeginOverlap(UPrimitiveComponent* OverlapperComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMyProjectCharacter* Player = Cast<AMyProjectCharacter>(OtherActor);
	if (Player != nullptr) {
		
		UCharacter_Skill* SkillComponent = Player->GetComponentBySkillType(SkillType);
		if(SkillComponent != nullptr && SkillComponent->increase()) {
			GEngine->AddOnScreenDebugMessage(5, 5, FColor::Red, FString::Printf(TEXT("test")));
			Destroy();
		}
	}
}


