// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

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

