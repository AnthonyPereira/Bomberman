// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomb.h"
#include "Wall.h"
#include "MyProjectCharacter.h"

#include "DestructableWall.h"
#include "Flame.h"

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
	ExplodeDirection(FVector::LeftVector);
	ExplodeDirection(FVector::RightVector);
	ExplodeDirection(FVector::ForwardVector);
	ExplodeDirection(FVector::BackwardVector);

	
	GetWorldTimerManager().ClearTimer(ExplodeTimerHandle);
	Destroy();
}


void ABomb::ExplodeDirection(FVector direction) {

	FVector Start = GetActorLocation() + direction*50;
	FVector End = (direction * 100.f * Density) + GetActorLocation();
	FCollisionQueryParams CollisionParams;
	const TArray<const AActor*> IgnoreActors = { this };
	TArray<FHitResult> Hits;
	CollisionParams.AddIgnoredActors(IgnoreActors);

	bool hit = GetWorld()->LineTraceMultiByChannel(Hits, Start, End, ECollisionChannel::ECC_GameTraceChannel1, CollisionParams);

	//DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1, 0, 15);
	size_t i = 0;

	FVector Endparticle = End;

	if (Hits.Num() > 0) {		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("%d"), Hits.Num()));

		for (i; i < Hits.Num(); i++)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, Hits[i].GetActor()->GetName());
			Endparticle = Hits[i].GetActor()->GetActorLocation();
			ADestructableWall* wallhit = Cast<ADestructableWall>(Hits[i].GetActor());
			if (wallhit != nullptr) {
				wallhit->Destroy();
				break;
			}

			

			ABomb* bomb = Cast<ABomb>(Hits[i].GetActor());

			if (bomb != nullptr && !bomb->Isexplode) {
				bomb->explode();
				break;
			}
			
		}
		//GEngine->AddOnScreenDebugMessage(-1, 35.f, FColor::White, FString::Printf(TEXT("start: %f,%f  distance %f,%f\n"), Start.X, Start.Y, End.X, End.Y));

	}
	FVector Currentpos = Start;
	int j = 0;
	if (direction.Y!=0) {
		while(Currentpos.Y != (Endparticle).Y && j!=15) {
			AFlame* Flame = GetWorld()->SpawnActorDeferred<AFlame>(FlameClass, FTransform(Currentpos));
			Flame->FinishSpawning(FTransform(Currentpos));
			Currentpos += direction*25;
			j++;
		}
	}


	int k = 0;
	if (direction.X != 0) {
		while (Currentpos.X != (Endparticle).X && k != 15) {
			AFlame* Flame = GetWorld()->SpawnActorDeferred<AFlame>(FlameClass, FTransform(Currentpos));
			Flame->FinishSpawning(FTransform(Currentpos));
			Currentpos += direction*25;
			k++;
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




