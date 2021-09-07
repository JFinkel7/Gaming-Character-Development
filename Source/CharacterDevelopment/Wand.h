// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h" 
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//
#include "Wand.generated.h"

UCLASS()
class CHARACTERDEVELOPMENT_API AWand : public AActor {
    GENERATED_BODY()

   	//! @brief: Weapon Capsule Collision 
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Capsule, meta = (AllowPrivateAccess = "true"))
    class UCapsuleComponent * capsuleComponent;

	//! @brief: Weapon Skeletal Mesh
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SkeletalMesh, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* skeletonMesh;


public:
    // Sets default values for this actor's properties
    AWand();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
};
