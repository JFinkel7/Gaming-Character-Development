// Fill out your copyright notice in the Description page of Project Settings.

#include "Dummy.h"

// Sets default values
ADummy::ADummy() {
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

	// [ROOT]
    meshVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootComponent"));
	meshVisual->SetCollisionProfileName(TEXT("Pawn"),true);
	UBodySetup* BodySetup = meshVisual->GetBodySetup(); 
	BodySetup->CollisionTraceFlag = ECollisionTraceFlag::CTF_UseComplexAsSimple;



	// Keyword: CollisionTraceFlag 
	// Keyword: ECollisionTraceFlag
	// Keyword: GetBodySetup()
	// Keyword: UBodySetup 

	//meshVisual->GetBodySetup()->CollisionTraceFlag = ECollisionTraceFlag::CTF_UseSimpleAsComplex;
    meshVisual->SetEnableGravity(true);
    meshVisual->SetSimulatePhysics(true);
    //meshVisual->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    //meshVisual->SetNotifyRigidBodyCollision(true);
	

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Current Name = %s"), *GetActor()));

	RootComponent = meshVisual;
	//meshVisual->SetupAttachment(RootComponent);

	// [COMPONENT]
	healthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	// [Static Mesh]
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Character_Box/Mesh/Default_Man.Default_Man"));
    if (MeshAsset.Succeeded()) {
        meshVisual->SetStaticMesh(MeshAsset.Object);		
    }

}

// Called when the game starts or when spawned
void ADummy::BeginPlay() {
    Super::BeginPlay();
	UBodySetup* BodySetup = meshVisual->GetBodySetup(); 
	BodySetup->CollisionTraceFlag = ECollisionTraceFlag::CTF_UseComplexAsSimple;
	
}

// Called every frame
void ADummy::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
}
