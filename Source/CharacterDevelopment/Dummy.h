// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//
#include "CharacterDevelopmentCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/InputComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "InputCoreTypes.h"
#include "UObject/ConstructorHelpers.h"
//
#include "Dummy.generated.h"

// (1) - Create (Actor) Class



UCLASS()
class CHARACTERDEVELOPMENT_API ADummy : public AActor {
    GENERATED_BODY()

    //! @brief: Sets Statich mesh component
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent *_meshVisual;

    //! @brief: Sets Collision component
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
    class USphereComponent *CollisionSphere;



public:
    // Sets default values for this actor's properties
    ADummy();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
    float MaxHealth = 100;

    UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = Health)
    float CurrentHealth = 100;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    virtual float TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController *EventInstigator, AActor *DamageCauser) override;

    // (3) - Create A (Custom) Event Method
    // That will respond when we hit the P key
    void Pickup();

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
};
