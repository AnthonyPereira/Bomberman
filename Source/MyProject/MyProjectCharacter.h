// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HealthComponent.h"
#include "MyInterface.h"
#include <MyProject\Character_Skill.h>

#include "MyProjectCharacter.generated.h"

UCLASS(config=Game)
class AMyProjectCharacter : public ACharacter, public IMyInterface
{
	GENERATED_BODY()

private:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	
public:
	AMyProjectCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;


	virtual void OnSpeedUpdate_Implementation() override;

	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = Health)
	class UHealthComponent* HealthComponent;

	virtual void OnDeath_Implementation() override;
	virtual void OnTakeDamage_Implementation() override;

	virtual void OnMeshUpdate_Implementation() override;

	//UFUNCTION(BlueprintNativeEvent, Category = Skills)
	//void MeshUpdate();

	UFUNCTION(BlueprintImplementableEvent, Category = Skills)
	void UpdateMyMesh();

	UFUNCTION(BlueprintImplementableEvent, Category = Skills)
	void Death();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Bomb)
	TSubclassOf<class ABomb> BombClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = speedMax)
	float SpeedMax=250;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TArray<UCharacter_Skill*> List_Skills;

	UFUNCTION(BlueprintCallable, Category = Skills)
	void ThrowBomb();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_ThrowBomb(FVector Location, FRotator Rotation, AMyProjectCharacter* PC, int flameSize);
	bool Server_ThrowBomb_Validate(FVector Location, FRotator Rotation, AMyProjectCharacter* PC, int flameSize);
	void Server_ThrowBomb_Implementation(FVector Location, FRotator Rotation, AMyProjectCharacter* PC, int flameSize);

	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void Multi_ThrowBomb(FVector Location, FRotator Rotation, AMyProjectCharacter* PC, int flameSize);
	bool Multi_ThrowBomb_Validate(FVector Location, FRotator Rotation, AMyProjectCharacter* PC, int flameSize);
	void Multi_ThrowBomb_Implementation(FVector Location, FRotator Rotation, AMyProjectCharacter* PC, int flameSize);



	int FloorHundred(float a);

	bool InBomb=false;



	UCharacter_Skill* GetComponentBySkillType(int type);


protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);



protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

