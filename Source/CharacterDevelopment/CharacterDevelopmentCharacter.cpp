// Copyright Epic Games, Inc. All Rights Reserved.

#include "CharacterDevelopmentCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"

ACharacterDevelopmentCharacter::ACharacterDevelopmentCharacter() {
    // Set size for collision capsule

    //GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
    GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

    // set our turn rates for input
    BaseTurnRate = 45.f;
    BaseLookUpRate = 45.f;

    // Don't rotate when the controller rotates. Let that just affect the camera.
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // Configure character movement
    GetCharacterMovement()->bOrientRotationToMovement = true;            // Character moves in the direction of input...
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
    GetCharacterMovement()->JumpZVelocity = 600.f;
    GetCharacterMovement()->AirControl = 0.2f;

    //Blueprint_Character

    // Create a camera boom (pulls in towards the player if there is a collision)
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 300.0f;       // The camera follows at this distance behind the character
    CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

    // Create a follow camera
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
    FollowCamera->bUsePawnControlRotation = false;                              // Camera does not rotate relative to arm

    // -----------------------------------[Character Mesh]--------------------------------------

    GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -100.0f));
    GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

    //Animation_V1.01
    //----------------------------------[Wand Mesh]---------------------------------------------
    // Create a gun mesh component
    wand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Wand"));
    wand->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
    wand->SetOnlyOwnerSee(false); // otherwise won't be visible in the multiplayer
    wand->bCastDynamicShadow = false;
    wand->CastShadow = false;
    wand->SetupAttachment(GetMesh());
    //----------------------------------[Shoot Location]-----------------------------------------
    shootingLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
    shootingLocation->SetupAttachment(wand);
    shootingLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));
    // FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
    //FP_Gun->SetupAttachment(RootComponent);
}

//=============================================================================================================
void ACharacterDevelopmentCharacter::BeginPlay() {
    Super::BeginPlay();
    // - Character Socket
    const FAttachmentTransformRules RULE = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true);
    wand->AttachToComponent(GetMesh(), RULE, TEXT("RightHand"));
    wand->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.0f));
}

//=============================================================================================================
void ACharacterDevelopmentCharacter::OnFire() {
    UWorld *const World = GetWorld();
    if (World != nullptr) {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Shot Fired"));
        FActorSpawnParameters ActorSpawnParams;
        ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
        const FVector SpawnLocation = shootingLocation->GetComponentLocation();
        const FRotator SpawnRotation = shootingLocation->GetComponentRotation();
        World->SpawnActor<AFireProjectile>(SpawnLocation, SpawnRotation, ActorSpawnParams);
    }
}

void ACharacterDevelopmentCharacter::onFireLineTrace() {
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("2"));
    // 1 - SET HitResult
    FHitResult OutHit;
    // 2 - GET Shooting Vector Location
    FVector Start = shootingLocation->GetComponentLocation();
    // 3 - GET Follow Camera Forward Vector
    FVector End = ((FollowCamera->GetForwardVector() * 1000.f) + Start);
    // 4 - SET Collision Params
    FCollisionQueryParams CollisionParams;
    // 5 - DRAW INFO
    DrawDebugLine(GetWorld(), Start, End, FColor::Green, true);
    // 6 - DRAW Line Trace
    bool bIsHit = GetWorld()->LineTraceSingleByChannel(
        OutHit,         // FHitResult object that will be populated with hit info
        Start,          // starting position
        End,            // end position
        ECC_Visibility, // collision channel - 3rd custom one
        CollisionParams // additional trace settings
    );
    // 7 - CHECK if Line trace hit an Object
    if (bIsHit) {
        // ~ GET - Object Hit Name
        GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s"), *OutHit.GetActor()->GetName()));

        // AActor * hitActor = OutHit.GetActor();

        // //hitActor->SetActorLocation(FVector(100.0f,100.0f,100.0f));
        // // OR
        // hitActor->SetActorLocation(FVector(100.0f,100.0f,100.0f),false);
        // // OR
        // //hitActor->SetActorLocation(FVector(100.0f,100.0f,100.0f),false, FHitResult,ETeleportType::TeleportPhysics);

        //GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("You are hitting: %s"), *hitActor->GetName()));
    }
}

void ACharacterDevelopmentCharacter::getMessage() {
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Message From Character"));
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ACharacterDevelopmentCharacter::SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) {
    // Set up gameplay key bindings
    check(PlayerInputComponent);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

    // new
    PlayerInputComponent->BindAction("Fire", IE_Released, this, &ACharacterDevelopmentCharacter::OnFire);
    // new
    PlayerInputComponent->BindAction("FireLineTrace", IE_Released, this, &ACharacterDevelopmentCharacter::onFireLineTrace);

    PlayerInputComponent->BindAxis("MoveForward", this, &ACharacterDevelopmentCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ACharacterDevelopmentCharacter::MoveRight);

    // We have 2 versions of the rotation bindings to handle different kinds of devices differently
    // "turn" handles devices that provide an absolute delta, such as a mouse.
    // "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis("TurnRate", this, &ACharacterDevelopmentCharacter::TurnAtRate);
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("LookUpRate", this, &ACharacterDevelopmentCharacter::LookUpAtRate);
}

//=============================================================================================================
void ACharacterDevelopmentCharacter::TurnAtRate(float Rate) {
    // calculate delta for this frame from the rate information
    AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

//=============================================================================================================
void ACharacterDevelopmentCharacter::LookUpAtRate(float Rate) {
    // calculate delta for this frame from the rate information
    AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

//=============================================================================================================
void ACharacterDevelopmentCharacter::MoveForward(float Value) {
    if ((Controller != nullptr) && (Value != 0.0f)) {
        // find out which way is forward
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // get forward vector
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, Value);
    }
}

//=============================================================================================================
void ACharacterDevelopmentCharacter::MoveRight(float Value) {
    if ((Controller != nullptr) && (Value != 0.0f)) {
        // find out which way is right
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // get right vector
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        // add movement in that direction
        AddMovementInput(Direction, Value);
    }
}
