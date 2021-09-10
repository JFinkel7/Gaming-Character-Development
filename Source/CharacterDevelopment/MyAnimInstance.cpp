// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAnimInstance.h"

// - Main
UMyAnimInstance::UMyAnimInstance() {
}

void UMyAnimInstance::UpdateAnimationProperties() {
    //Get the pawn which is affected by our anim instance
    APawn *Pawn = TryGetPawnOwner();

    if (Pawn) {
        //Update our falling property
        bIsFalling = Pawn->GetMovementComponent()->IsFalling();

        //Update our movement speed
        MovementSpeed = Pawn->GetVelocity().Size();
    }
}