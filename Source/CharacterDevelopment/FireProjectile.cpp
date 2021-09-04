// Fill out your copyright notice in the Description page of Project Settings.

#include "FireProjectile.h"

AFireProjectile::AFireProjectile() {
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // - (1) Create Collision Sphere Component
    CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
    CollisionSphere->InitSphereRadius(50.0f);
    CollisionSphere->SetCollisionProfileName(TEXT("Pawn"));
    CollisionSphere->SetEnableGravity(true);
    CollisionSphere->SetSimulatePhysics(true);
    CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    CollisionSphere->SetNotifyRigidBodyCollision(true);
    CollisionSphere->OnComponentHit.AddDynamic(this, &AFireProjectile::OnHit);
    RootComponent = CollisionSphere;


    // - Create Visual Static Mesh Component
    SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
    SphereVisual->SetupAttachment(CollisionSphere);

    // - Load The Static Mesh
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/Assets/Shapes/Ball.Ball"));
    if (SphereVisualAsset.Succeeded()) {
        SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
    }

    //Hit contains information about what the line trace hit.
    //FHitResult Hit;
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));

    if (ProjectileMovement != NULL) {
        // - Set Stats
        ProjectileMovement->UpdatedComponent = CollisionSphere;
        ProjectileMovement->InitialSpeed = 3000.f;
        ProjectileMovement->MaxSpeed = 3000.f;
        ProjectileMovement->bRotationFollowsVelocity = true;
        ProjectileMovement->bShouldBounce = true;
        ProjectileMovement->Bounciness = 0.3f;
    }

    // Die after 5 seconds by default
    InitialLifeSpan = 5.0f;
}

void AFireProjectile::OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit) {
    // Only add impulse and destroy projectile if we hit a actor has physics
    //if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) & OtherComp->IsSimulatingPhysics()){
    // Only add impulse and destroy projectile if we hit a physics
    if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics()) {  
              
        OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());


        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("I Hit Actor:  %s"), *OtherActor->GetName()));
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("I Hit Component:  %s"), *HitComp->GetName()));

      

        //OtherComp->AddForce(FVector(50.0f,50.0f,50.0f)*OtherComp->GetMass());
        //OtherComp

        //ProjectileMovement->Velocity = FVector(0.0f, 5.0f, 0.0f) * ProjectileMovement->InitialSpeed;
        // - Moves The Component
        //ProjectileMovement->AddForce(FVector(50.0f,50.0f,50.0f));
        //Destroy();
    }
}

// Called when the game starts or when spawned
void AFireProjectile::BeginPlay() {
    Super::BeginPlay();
}

// Called every frame
void AFireProjectile::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
}
