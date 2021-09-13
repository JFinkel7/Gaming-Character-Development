// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAnimInstance.h"

// - Main
UMyAnimInstance::UMyAnimInstance() {
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Constructor = True"));
    //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Updating:  %d"), bIsFalling));
}

void UMyAnimInstance::UpdateAnimationProperties() {
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("UpdateAnimation = True"));
    // //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ANIM - Updating = True"));
    APawn *owner = TryGetPawnOwner();
    if (owner != NULL) {
        //Update our falling property
        bIsFalling = owner->GetMovementComponent()->IsFalling();

        //Update our movement speed
        MovementSpeed = owner->GetVelocity().Size();
    }
}