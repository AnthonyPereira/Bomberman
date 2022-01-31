// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Patate.generated.h"


UCLASS()
class MYPROJECT_API APatate : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Patate, meta = (AllowPrivateAccess = "true"));
	class USphereComponent* SphereComponent;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Patate, meta = (AllowPrivateAccess = "true"));
	class  UProjectileMovementComponent *ProjectileMovement;




public:	
	// Sets default values for this actor's properties
	APatate();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* Hitcomp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovementComponent() const
	{
		return ProjectileMovement;
	}

	float Damage = 15.f;
protected:

	UPROPERTY(EditAnywhere, Category = Sound);
	class USoundBase* BounceSound;

	UPROPERTY(EditAnywhere, Category = Sound);
	class USoundAttenuation* BounceSoundAttenuation;


	UPROPERTY(EditAnywhere, Category = Sound);
	class USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category = Sound);
	class USoundAttenuation* HitSoundAttenuation;

	UPROPERTY(EditAnywhere, Category = Particles);
	class UParticleSystem* HitParticles;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
