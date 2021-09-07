// Fill out your copyright notice in the Description page of Project Settings.

#include "Dummy.h"

// Sets default values
ADummy::ADummy() {
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // [ROOT]
    _meshVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootComponent"));
    _meshVisual->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    _meshVisual->SetCollisionProfileName(TEXT("Pawn"), true);
    _meshVisual->SetNotifyRigidBodyCollision(true);
    _meshVisual->SetSimulatePhysics(true);
    _meshVisual->SetEnableGravity(true);
    // - PARENT
    _meshVisual->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

    // [COMPONENT]
    _healthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

// Called when the game starts or when spawned
void ADummy::BeginPlay() {
    Super::BeginPlay();
 

    //_healthComponent->TakeDamage(this,10.00f,UDamageType::StaticClass(),NULL,NULL);
}

// Called every frame
void ADummy::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
}

float ADummy::TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController *EventInstigator, AActor *DamageCauser) {
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("I Was Damaged!"));
    return (0.0f);
}

void ADummy::ReceiveAnyDamage(float Damage, const class UDamageType *DamageType, class AController *InstigatedBy, AActor *DamageCauser) {
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Health Component Hit Registered"));
    //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Damage Was Taken By Actor: %s"), *DamagedActor->GetName()));
}
