// Fill out your copyright notice in the Description page of Project Settings.

#include "Dummy.h"

// Sets default values
ADummy::ADummy() {
    // (4) - Configure Our Constructor
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;
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

    //CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger Capsule"));
    //CollisionSphere->InitSphereRadius(55.0f);

    //CollisionSphere->SetCollisionProfileName(TEXT("Trigger"));
    //CollisionSphere->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADummy::BeginPlay() {
    Super::BeginPlay();
    // - Create UWorld Instance
    UWorld *world = GetWorld();
    if (world != NULL) {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("(World)->Valid"));
        // - GET our Player Controller
        APlayerController *controller = world->GetFirstPlayerController();
        if (controller != NULL) {
            // - Enable Input
            ADummy::EnableInput(controller);
            InputComponent->bBlockInput = false;
            FInputActionBinding Binding = InputComponent->BindAction(TEXT("Pickup"), IE_Pressed, this, &ADummy::Pickup);
            Binding.bConsumeInput = false;
        }
    }

  
}

//=========================================[Pick Up Object]=======================================
void ADummy::Pickup() {
    // #include "CharacterDevelopmentCharacter.h"
   // Then Varable and cast it on this Actor (ADummy)                           ↓
    // NOTE: Our Current Actor Is A Stick 
    // (1) - Cast Our Character
    class ACharacterDevelopmentCharacter *characterPtr = Cast<ACharacterDevelopmentCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));

    if (characterPtr != nullptr) {
        // (2) - Create A Rule 
        const FAttachmentTransformRules RULE = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true);
        // (3) - Attatch Our Stick (_meshVisual) To Character Left Hand 
        _meshVisual->AttachToComponent(characterPtr->GetWeaponSkeletalMesh(),RULE,TEXT("LeftHand"));
    }

    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Picked Up Item"));
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
