// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent() {
    // Set this component to be initialized when the game starts, and to be ticked every frame.  
    //You can turn these features off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;
    // (3) - Declare Your Variables here 
    max_health = 100;
    min_health = 0;

}

// Called when the game starts
void UHealthComponent::BeginPlay() {
    Super::BeginPlay();
    // (4) - Gets The Actor That This Component Is Attatched To 
    AActor *current_actor = GetOwner();
    if (current_actor != nullptr) {
         GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Current Name = %s"), *current_actor->GetName()));

        current_actor->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
    }

    // ...
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
}

//================================================================================================================
void UHealthComponent::TakeDamage(AActor *DamagedActor, float Damage, const class UDamageType *DamageType, class AController *InstigatedBy, AActor *DamageCauser) {
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Damage Was Taken By Actor: %s"), *DamagedActor->GetName()));
}
