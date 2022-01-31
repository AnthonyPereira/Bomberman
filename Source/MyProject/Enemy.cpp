// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "EscapeFunctionLibrary.h"
#include "TimerManager.h"
#include "LookAtComponent.h"

#include <DrawDebugHelpers.h>
#include <Kismet/KismetMathLibrary.h> 
#include <Kismet/Gameplaystatics.h> 
#include "Engine/World.h"
#include <GameFramework/ProjectileMovementComponent.h>



// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LookAtComponent = CreateDefaultSubobject<ULookAtComponent>(TEXT("Sight Source"));
	LookAtComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	ACharacter*Player = UGameplayStatics::GetPlayerCharacter(this, 0);
	LookAtComponent->SetTarget(Player);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	bCanSeePlayer = LookAtComponent->LookAtActor();

	if (bCanSeePlayer != bPreviousCanSeePlayer) {

		if (bCanSeePlayer) {
			//start timer
			GetWorldTimerManager().SetTimer(ThrowTimerHandle,this,&AEnemy::ThrowPatate,ThrowingInterval,true,ThrowingDelay);

		}
		else {
			//stop timer		
			//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::White, TEXT("Patate"));
			GetWorldTimerManager().ClearTimer(ThrowTimerHandle);
		}
	}		
	bPreviousCanSeePlayer = bCanSeePlayer;


}

void AEnemy::ThrowPatate() {
	if (PatateClass == nullptr) {
		return;
	}
	FVector ForwardVector = GetActorForwardVector();
	float SpawnDistance = 40.f;
	FVector SpawnLocation = GetActorLocation() + (ForwardVector * SpawnDistance);
	FTransform SpawnTransform(GetActorRotation(),SpawnLocation);

	APatate* Patate = GetWorld()->SpawnActorDeferred<APatate>(PatateClass,SpawnTransform);
	Patate->GetProjectileMovementComponent()->InitialSpeed = 2200.f;
	Patate->FinishSpawning(SpawnTransform);




	//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::White, TEXT("Patate!!"));
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}





