// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "Animation/AnimSequence.h"
#include "CharacterDevelopmentCharacter.h"
#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "MyAnimInstance.generated.h"

UCLASS()
class CHARACTERDEVELOPMENT_API UMyAnimInstance : public UAnimInstance {
    GENERATED_BODY()

public:
    UMyAnimInstance();

protected:
    //! @brief: True means that we're currently in air - or falling
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    bool bIsFalling;

    //! @brief: Holds the current speed of our character
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float MovementSpeed;

    //! @brief: Updates the above properties
    UFUNCTION(BlueprintCallable, Category = "UpdateAnimationProperties")
    void UpdateAnimationProperties();
};
