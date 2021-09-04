// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "HealthComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
// (1) - Create A Custom Class that extends UActor Component 
class CHARACTERDEVELOPMENT_API UHealthComponent : public UActorComponent {
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    //! @brief: Constructor 
    UHealthComponent();
    // (2) - Create Class Variables 
    UPROPERTY(EditAnywhere, Category = Health)
    float max_health;

    UPROPERTY(EditAnywhere, Category = Health)
    float min_health;

public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

    // - Called When Actor Takes Damage
    void TakeDamage(AActor *DamagedActor, float Damage, const class UDamageType *DamageType, class AController *InstigatedBy, AActor *DamageCauser);
};
