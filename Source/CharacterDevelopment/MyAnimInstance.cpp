// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAnimInstance.h"

// - Main
UMyAnimInstance::UMyAnimInstance() {
    //C:\Users\User\Documents\Unreal Projects\CharacterDevelopment\Content\TBot\Animation
    static ConstructorHelpers::FObjectFinder<UAnimSequence> animation(TEXT("/Game/TBot/Animation/Jumping_Up.Jumping_Up"));
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Constructor = True"));
    _jumpSequencePtr = animation.Object;
    //bool isLooping = false;
    //this->GetMesh()->PlayAnimation(_jumpSequencePtr,isLooping);
}

void UMyAnimInstance::NativeInitializeAnimation() {
    Super::NativeInitializeAnimation();
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("NativeInitialize = True"));
    _owner = TryGetPawnOwner();
    if (_owner != NULL) {
        // - Cast Character
        _playerCharacter = Cast<ACharacterDevelopmentCharacter>(_owner);
        if (_playerCharacter != NULL) {
            // - Do Something Here
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Character !NULL"));
        }
    }
}


void UMyAnimInstance::PostInitProperties(){
  GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("PostInit = True"));
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds) {
}

void UMyAnimInstance::UpdateAnimationProperties() {
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("UpdateAnimation = True"));
    // //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ANIM - Updating = True"));
    // if (Owner != NULL) {
    //     //Update our falling property
    //     bIsFalling = Owner->GetMovementComponent()->IsFalling();

    //     //Update our movement speed
    //     MovementSpeed = Owner->GetVelocity().Size();
    //    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Updating:  %d"), bIsFalling));

    // }
}