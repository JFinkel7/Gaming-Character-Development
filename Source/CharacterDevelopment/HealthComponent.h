// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "HealthComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CHARACTERDEVELOPMENT_API UHealthComponent : public UActorComponent {
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UHealthComponent();

  UPROPERTY(EditAnywhere, Category = Health)
  float max_health;
  
  UPROPERTY(EditAnywhere, Category = Health)
  float min_health;

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

	// - Called When Actor Takes Damage 
	void TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
};
