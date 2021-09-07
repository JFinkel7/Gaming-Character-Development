// Fill out your copyright notice in the Description page of Project Settings.

#include "Wand.h"

// Sets default values
AWand::AWand() {
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;
	
	// [Collsion]
	//----------------------------------------------
    capsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("RootComponent"));
    capsuleComponent->InitCapsuleSize(10.0f,10.0f);
    capsuleComponent->SetCollisionProfileName(TEXT("Pawn"));
    RootComponent = capsuleComponent;

	// [Skeletal Mesh]
	//----------------------------------------------
	skeletonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WandSkeleton"));
    skeletonMesh->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
    skeletonMesh->SetOnlyOwnerSee(true); // otherwise won't be visible in the multiplayer
    skeletonMesh->bCastDynamicShadow = false;
    skeletonMesh->CastShadow = false;
    skeletonMesh->SetupAttachment(capsuleComponent);




}

// Called when the game starts or when spawned
void AWand::BeginPlay() {
    Super::BeginPlay();
}

// Called every frame
void AWand::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
}
