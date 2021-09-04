// Fill out your copyright notice in the Description page of Project Settings.

#include "Dummy.h"

// Sets default values
ADummy::ADummy() {
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

	// [ROOT]
    meshVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootComponent"));
	meshVisual->SetCollisionProfileName(TEXT("Pawn"),true);
	meshVisual->SetEnableGravity(true);
	meshVisual->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	meshVisual->SetNotifyRigidBodyCollision(true);
	RootComponent = meshVisual;
	// [COMPONENT]
	healthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));


 
    //meshVisual->SetSimulatePhysics(true);
    //meshVisual->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    //meshVisual->SetNotifyRigidBodyCollision(true);
	

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Current Name = %s"), *GetActor()));


	

	// [Static Mesh]
	// class UStaticMesh* meshAsset = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), 
	// 								NULL, TEXT("/Game/Character_Box/Mesh/Default_Man.Default_Man")));
	
	UStaticMesh* meshAsset = NewObject<UStaticMesh>(UStaticMesh::StaticClass(),NULL, TEXT("/Game/Character_Box/Mesh/Default_Man.Default_Man"));
	
    if (meshAsset!= nullptr) {
		
        meshVisual->SetStaticMesh(meshAsset);		
    }

}

// Called when the game starts or when spawned
void ADummy::BeginPlay() {
    Super::BeginPlay();

	
}

// Called every frame
void ADummy::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
}
