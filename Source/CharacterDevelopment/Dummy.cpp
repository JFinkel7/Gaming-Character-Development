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
	_meshVisual->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepRelativeTransform);

	// [COMPONENT]
    _healthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
    


}

// Called when the game starts or when spawned
void ADummy::BeginPlay() {
    Super::BeginPlay();
}

// Called every frame
void ADummy::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
}
