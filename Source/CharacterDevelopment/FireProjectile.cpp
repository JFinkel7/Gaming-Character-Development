// Fill out your copyright notice in the Description page of Project Settings.

#include "FireProjectile.h"

AFireProjectile::AFireProjectile() {
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // - (1) Create Collision Sphere Component
    CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
    CollisionSphere->InitSphereRadius(50.0f);
    CollisionSphere->SetCollisionProfileName(TEXT("Pawn"));
    CollisionSphere->OnComponentHit.AddDynamic(this, &AFireProjectile::OnHit);	
    CollisionSphere->SetEnableGravity(true);
    CollisionSphere->SetSimulatePhysics(true);
    CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    
    //CollisionSphere->SetupAttachment(RootComponent);
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
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("TRUE"));
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

    // Die after 3 seconds by default
   //InitialLifeSpan = 3.0f;
}


void AFireProjectile::OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit) {
    // Only add impulse and destroy projectile if we hit a actor has physics
    if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) & OtherComp->IsSimulatingPhysics()) {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Hit Started"));
        OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());        
        //ProjectileMovement->Velocity = FVector(0.0f, 5.0f, 0.0f) * ProjectileMovement->InitialSpeed;
        // - Moves The Component
        //ProjectileMovement->AddForce(FVector(50.0f,50.0f,50.0f));
       
        Destroy();
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
