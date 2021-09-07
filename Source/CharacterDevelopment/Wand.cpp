// Fill out your copyright notice in the Description page of Project Settings.

#include "Wand.h"

// Sets default values
AWand::AWand() {
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    // [Collsion]
    //----------------------------------------------
    capsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("RootComponent"));
    capsuleComponent->InitCapsuleSize(1.0f, 60.0f);
    capsuleComponent->SetCollisionProfileName(TEXT("Pawn"));
    RootComponent = capsuleComponent;

    // [Skeletal Mesh]
    //----------------------------------------------
    skeletonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WandSkeleton"));
    skeletonMesh->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
    //skeletonMesh->SetOnlyOwnerSee(false); // otherwise won't be visible in the multiplayer
    skeletonMesh->bCastDynamicShadow = false;
    skeletonMesh->CastShadow = false;
    skeletonMesh->SetupAttachment(capsuleComponent);

    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("[Wand] - Constructor Called"));
}

// Called when the game starts or when spawned
void AWand::BeginPlay() {
    Super::BeginPlay();
    //**** ***/
    FHitResult OutHit;
    FVector Start = AWand::GetActorLocation();
    FVector ForwardVector = RootComponent->GetForwardVector();
    FVector End = ((ForwardVector * 1000.f) + Start);


    FCollisionQueryParams CollisionParams;

    DrawDebugLine(GetWorld(), Start, End, FColor::Green, true);

    if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams)) {
        if (OutHit.bBlockingHit) {
            GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s"), *OutHit.GetActor()->GetName()));
            GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Purple, FString::Printf(TEXT("Impact Point: %s"), *OutHit.ImpactPoint.ToString()));
            GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("Normal Point: %s"), *OutHit.ImpactNormal.ToString()));
        }
    }
}

// Called every frame
void AWand::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
}
