// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAnimInstance.h"

// - Main
UMyAnimInstance::UMyAnimInstance() {
    Owner = TryGetPawnOwner()
    //C:\Users\User\Documents\Unreal Projects\CharacterDevelopment\Content\TBot\Animation
    static ConstructorHelpers::FObjectFinder<UAnimSequence> animation(TEXT("/Game/TBot/Animation/Jumping_Up.Jumping_Up"));
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ANIM - Constructor = True"));
    _jumpSequencePtr = animation.Object;
    //bool isLooping = false;
    //this->GetMesh()->PlayAnimation(_jumpSequencePtr,isLooping);
}



void UMyAnimInstance::NativeInitializeAnimation(){
    Super::NativeInitializeAnimation();
    // (1) - Get Pawn Owner Reference (Which is our Character that is using this animation)
    //APawn *Owner = TryGetPawnOwner();
    // (2) - Cast Our Character 
    ACharacterDevelopmentCharacter * PlayerCharacter = Cast<ACharacterDevelopmentCharacter>(Owner);

    if(PlayerCharacter != NULL){
        // (3) - Call Our Character Class Methods 
        bIsFalling = PlayerCharacter->GetMovementComponent()->IsFalling();

        //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("True"));
        //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("I Hit Actor:  %s"), result));

    }
}


void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds){
    //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Updating:  %d"), DeltaSeconds));
    bIsFalling = Owner->GetMovementComponent()->IsFalling();
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Updating:  %d"), bIsFalling));

}

void UMyAnimInstance::UpdateAnimationProperties() {


    // //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ANIM - Updating = True"));
    // if (Owner != NULL) {
    //     //Update our falling property
    //     bIsFalling = Owner->GetMovementComponent()->IsFalling();

    //     //Update our movement speed
    //     MovementSpeed = Owner->GetVelocity().Size();
    // }
}