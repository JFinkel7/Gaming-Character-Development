// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
//
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h" 
#include "FireProjectile.h"
//
#include "CharacterDevelopmentCharacter.generated.h"

UCLASS(config=Game)
class ACharacterDevelopmentCharacter : public ACharacter{
	GENERATED_BODY()

	//! @brief: Maintain its children at a fixed distance from the parent
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	//! @brief: Follow Camera 	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/** Gun mesh: VR view (attached to the VR controller directly, no arm, just the actual gun) */
	UPROPERTY(VisibleDefaultsOnly, Category = SkeletalMesh)
	// OLD FP_Gun
	class USkeletalMeshComponent* wand;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	// OLD FP_MuzzleLocation
	class USceneComponent* shootingLocation;
	
	//UPROPERTY(VisibleDefaultsOnly, Category = Socket)
	//class  USkeletalMeshSocket *socketInstance;

public:
	//! @brief: Constructor 
	ACharacterDevelopmentCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:
	//! @brief: Sets Up Our Controller Input  
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	//! @brief: Called When We Start The Game 
	virtual void BeginPlay();

	//! @brief: Function will create a instance of a fire actor projectile 
	/** Fires a projectile. */
	void OnFire();

protected:
	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/**  Called via input to turn at a given rate.  @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate*/
	void TurnAtRate(float Rate);

	/**Called via input to turn look up/down at a given rate.  @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate*/
	void LookUpAtRate(float Rate);


};

