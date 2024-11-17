// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/InteractableObject.h"

#include "Components/SceneCaptureComponent2D.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

AInteractableObject::AInteractableObject()
{
    PrimaryActorTick.bCanEverTick = true;
    
    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
    SceneCaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureComponent2D"));
}

void AInteractableObject::BeginPlay()
{
    Super::BeginPlay();
}

void AInteractableObject::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    StaticMeshComponent->AddRelativeRotation(RotationSpeed);
}

void AInteractableObject::ZoonInOut(float Value)
{
    if(abs(ZoomCount) <= 30)
    {
        SceneCaptureComponent->AddWorldTransform(FTransform(TransformSpeed * Value));
        ZoomCount += Value;
    }
    else if(ZoomCount >= 30)
    {
        if(Value < 0.f) ZoomCount--;
    }
    else if(ZoomCount <= -30)
    {
        if(Value > 0.f) ZoomCount++;
    } 
}

void AInteractableObject::SetStaticMesh(UStaticMesh* StaticMesh, TArray<UMaterialInterface*> Materials)
{
    StaticMeshComponent->SetStaticMesh(StaticMesh);
    
    for (int32 i = 0; i < Materials.Num(); ++i)
    {
        StaticMeshComponent->SetMaterial(i, Materials[i]);
    }
}
