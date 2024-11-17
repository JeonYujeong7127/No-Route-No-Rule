// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableObject.generated.h"

UCLASS()
class NOROUTENORULE_API AInteractableObject : public AActor
{
	GENERATED_BODY()
    
public:
	AInteractableObject();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	const FRotator RotationSpeed = FRotator(0.f, 0.5f, 0.f);
	const FVector TransformSpeed = FVector(-10.f, 0.f, 0.f);
	
public:
	virtual void ZoonInOut(float Value);
    virtual void SetStaticMesh(class UStaticMesh* StaticMesh, TArray<UMaterialInterface*> Materials);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneCaptureComponent2D> SceneCaptureComponent;

private:
	int8 ZoomCount = 0;
};
