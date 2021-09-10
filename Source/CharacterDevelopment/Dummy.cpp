// Fill out your copyright notice in the Description page of Project Settings.

#include "Dummy.h"

// Sets default values
ADummy::ADummy() {
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    //CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger Capsule"));
    //CollisionSphere->InitSphereRadius(55.0f);

    //CollisionSphere->SetCollisionProfileName(TEXT("Trigger"));
    //CollisionSphere->SetupAttachment(RootComponent);

    // [ROOT]
    _meshVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootComponent"));
    _meshVisual->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    _meshVisual->SetCollisionProfileName(TEXT("Pawn"), true);
    _meshVisual->SetNotifyRigidBodyCollision(true);
    _meshVisual->SetSimulatePhysics(true);
    _meshVisual->SetEnableGravity(true);
    // - PARENT
    _meshVisual->SetupAttachment(RootComponent);
    _meshVisual->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

    ActorInputComponent = CreateDefaultSubobject<UInputComponent>("InputComponent");

  
}

// Called when the game starts or when spawned
void ADummy::BeginPlay() {
    Super::BeginPlay();
    // 


    UWorld * world = GetWorld();
    if(world != NULL){
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("(World)-> !NULL"));
        APlayerController* controller  = world->GetFirstPlayerController();
        if(controller != NULL){
            ADummy::EnableInput(controller);
            ActorInputComponent->bBlockInput = false;
            FInputActionBinding Binding = InputComponent->BindAction(TEXT("Test"), IE_Pressed, this, &ADummy::SaveGame);
            Binding.bConsumeInput = false;
            //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("(Controller)-> !NULL"));
            //controller->BindAction("Test", IE_Pressed, this, &ADummy::SaveGame);
            //InputComponent->BindKey(EKeys::A, IE_Released, this, &ADummy::jumpCallback);
            //bool isKeyDown = controller->IsInputKeyDown(EKeys::T);
            // if(controller->WasInputKeyJustPressed(EKeys::B)){
            //     GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Key T Down"));
            // }
        }
    }

    //_healthComponent->TakeDamage(this,10.00f,UDamageType::StaticClass(),NULL,NULL);
}

//=========================================[INPUT]=======================================

void ADummy::SaveGame() {
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Saved"));
}
// Called every frame
void ADummy::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
}

float ADummy::TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController *EventInstigator, AActor *DamageCauser) {
    const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Applying Damage!"));
    CurrentHealth -= ActualDamage;
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Damage Was Taken By Actor: %f"), CurrentHealth));

    if (CurrentHealth <= 0.0f) {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Character Is Dead"));
        ADummy::Destroy();
    }

    return ActualDamage;
}
