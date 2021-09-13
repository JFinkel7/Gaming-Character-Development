// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAnimInstance.h"

// - Main
UMyAnimInstance::UMyAnimInstance() {
    //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Updating:  %d"), bIsFalling));
}

void UMyAnimInstance::UpdateAnimationProperties() {
    if (TryGetPawnOwner() != NULL) {
        //Update our falling property
        bIsFalling = TryGetPawnOwner()->GetMovementComponent()->IsFalling();

        //Update our movement speed
        MovementSpeed = TryGetPawnOwner()->GetVelocity().Size();
    }
}



void UMyAnimInstance::Attack(){
    //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Attack Moves")));

}