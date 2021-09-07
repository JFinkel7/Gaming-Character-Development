// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//
#include "UObject/ConstructorHelpers.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "HealthComponent.h"
//
#include "Dummy.generated.h"

UCLASS()
class CHARACTERDEVELOPMENT_API ADummy : public AActor {
    GENERATED_BODY()

    /** Statich mesh component **/
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent *_meshVisual;

	/** Health component **/
   	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
    class UHealthComponent* _healthComponent;

public:
    // Sets default values for this actor's properties
    ADummy();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;
//================================================================================================================
    void ReceiveAnyDamage(float Damage, const class UDamageType * DamageType, class AController * InstigatedBy, AActor * DamageCauser);
public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
};
