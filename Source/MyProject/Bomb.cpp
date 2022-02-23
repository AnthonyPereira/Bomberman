// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomb.h"
#include "Wall.h"
#include "MyProjectCharacter.h"

#include "DestructableWall.h"
#include "HealthComponent.h"

#include <DrawDebugHelpers.h>
#include <Kismet/KismetMathLibrary.h> 
#include <Kismet/Gameplaystatics.h> 
#include <Components/SphereComponent.h>

// Sets default values
ABomb::ABomb()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("BOMB"));
	SphereComponent->SetSimulatePhysics(true);
	SphereComponent->SetSphereRadius(50.f);
	SphereComponent->SetNotifyRigidBodyCollision(true);
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABomb::OnBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ABomb::OnComponentEndOverlap);
	RootComponent = SphereComponent;
}

ABomb::ABomb(int density)
{
	ABomb();
	this->Density = density;
}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(ExplodeTimerHandle, this, &ABomb::explode, 0.1f, true, 3.0f);
	
}

void ABomb::explode() {
	Isexplode = true;
	ExplodeDirection(GetActorLocation()+FVector::LeftVector * 40, (FVector::LeftVector * 100.f * Density) + GetActorLocation());
	ExplodeDirection(GetActorLocation()+FVector::RightVector* 50, (FVector::RightVector * 100.f * Density) + GetActorLocation());
	ExplodeDirection(GetActorLocation()+ FVector::ForwardVector* 50, (FVector::ForwardVector * 100.f * Density) + GetActorLocation());
	ExplodeDirection(GetActorLocation()+ FVector::BackwardVector*50, (FVector::BackwardVector * 100.f * Density) + GetActorLocation());

	
	GetWorldTimerManager().ClearTimer(ExplodeTimerHandle);
	Destroy();
}


void ABomb::ExplodeDirection(FVector start , FVector end) {


	FCollisionQueryParams CollisionParams;
	const TArray<const AActor*> IgnoreActors = { this };
	TArray<FHitResult> Hits;
	CollisionParams.AddIgnoredActors(IgnoreActors);

	bool hit = GetWorld()->LineTraceMultiByChannel(Hits, start, end, ECollisionChannel::ECC_GameTraceChannel1, CollisionParams);

	DrawDebugLine(GetWorld(), start, end, FColor::Red, false, 1, 0, 15);

	if (Hits.Num()>0) {
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("%d"), Hits.Num()));

		
		for (size_t i = 0; i < Hits.Num(); i++)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, Hits[i].GetActor()->GetName());

			ADestructableWall* wallhit = Cast<ADestructableWall>(Hits[i].GetActor());
			if (wallhit != nullptr) {
				wallhit->Destroy();
				break;
			}
			
			AMyProjectCharacter* Player = Cast<AMyProjectCharacter>(Hits[i].GetActor());

			if (Player != nullptr) {
				UHealthComponent* HealthComponent = Player->FindComponentByClass<UHealthComponent>();
				HealthComponent->LoseHealth(1.f);
				continue;
			}

			ABomb* bomb = Cast<ABomb>(Hits[i].GetActor());

			if (bomb != nullptr && !bomb->Isexplode) {
				bomb->explode();
			}
		}
	}
}

// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void ABomb::OnComponentEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	SphereComponent->SetCollisionProfileName(FName("BlockAll"));
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::White, FString::Printf(TEXT("dehors : %f:%f"), GetActorLocation().X, GetActorLocation().Y));

}

void ABomb::OnBeginOverlap(UPrimitiveComponent* OverlapperComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::White, FString::Printf(TEXT("%f:%f"), GetActorLocation().X, GetActorLocation().Y));

}

void ABomb::SetDensity(int i) {
	Density=i;
}




