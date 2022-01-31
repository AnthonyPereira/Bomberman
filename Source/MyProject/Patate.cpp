// Fill out your copyright notice in the Description page of Project Settings.


#include "Patate.h"
#include "MyProjectCharacter.h"
#include "HealthComponent.h"
#include <Components/SphereComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <Kismet/GameplayStatics.h>

// Sets default values
APatate::APatate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("PATATE"));
	SphereComponent->SetSphereRadius(10.f);
	SphereComponent->SetCollisionProfileName(FName("Patatepreset"));
	SphereComponent->SetSimulatePhysics(true);
	SphereComponent->SetNotifyRigidBodyCollision(true);
	SphereComponent->OnComponentHit.AddDynamic(this, &APatate::OnHit);
	RootComponent = SphereComponent;
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));
	ProjectileMovement->InitialSpeed = 1500.f;



}

void APatate::OnHit(UPrimitiveComponent* Hitcomp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AMyProjectCharacter* Player = Cast<AMyProjectCharacter>(OtherActor);

	if (BounceSound != nullptr && NormalImpulse.Size()> 300) {
		UGameplayStatics::PlaySoundAtLocation(this, BounceSound, GetActorLocation(),1.f,1.f,0.f,BounceSoundAttenuation);
	}

	

	if (Player != nullptr) {

		if (HitSound != nullptr && NormalImpulse.Size() > 300) {
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation(), 1.f, 1.f, 0.f, HitSoundAttenuation);
		}

		if (HitParticles != nullptr) {
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticles, OtherComp->GetComponentTransform());
		}
		UHealthComponent* HealthComponent = Player->FindComponentByClass<UHealthComponent>();
		if (HealthComponent)
		{
			HealthComponent->LoseHealth(Damage);
		}

		
		Destroy();
	}
}

// Called when the game starts or when spawned
void APatate::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentHit.AddDynamic(this, &APatate::OnHit);
	SetLifeSpan(5.f);
	
}

// Called every frame
void APatate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

