// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bomb.generated.h"

UCLASS()
class MYPROJECT_API ABomb : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Explosion, meta = (AllowPrivateAccess = "true"));
	class USphereComponent* SphereComponent;

	
private:
	int Density = 1;

	
public:	
	// Sets default values for this actor's properties
	ABomb();

	ABomb(int density);

	FTimerHandle ExplodeTimerHandle;
	bool Isexplode = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Explosion)
	TSubclassOf<class AFlame> FlameClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void explode();

	void ExplodeDirection(FVector direction);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void OnComponentEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlapperComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SetDensity(int i);

};
