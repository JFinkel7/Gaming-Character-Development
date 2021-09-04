// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
// - Personal Imports 
#include "UObject/ConstructorHelpers.h"
#include "Components/SceneComponent.h"
#include "PhysicsEngine/BodySetup.h" 
//
#include "HealthComponent.h"
//
#include "Dummy.generated.h"

UCLASS()
class CHARACTERDEVELOPMENT_API ADummy : public AActor{
	GENERATED_BODY()

	/** Scene component **/
   	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
    // class USceneComponent* sceneComponent;

	/** Statich mesh component **/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent * meshVisual;

	/** Health component **/
   	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
    class UHealthComponent* healthComponent;
	
public:	
	// Sets default values for this actor's properties
	ADummy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
