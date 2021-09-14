// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAnimInstance.h"

// - Main
UMyAnimInstance::UMyAnimInstance() {
    //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Updating:  %d"), bIsFalling));
}

void UMyAnimInstance::UpdateAnimationProperties() {
    APawn *owner = TryGetPawnOwner();
    if (owner != NULL) {
        //Update our falling property
        bIsFalling = owner->GetMovementComponent()->IsFalling();

        //Update our movement speed
        MovementSpeed = owner->GetVelocity().Size();
    }
}

void UMyAnimInstance::Punch() {
    // - If Animation is Equiped
    if (PunchAnimation != NULL) {
        Montage_Play(PunchAnimation, 1.0f);
        //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Punch")));
    }
    //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Attack Moves")));
}