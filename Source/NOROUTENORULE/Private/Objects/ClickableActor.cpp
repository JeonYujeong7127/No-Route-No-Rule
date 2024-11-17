// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/ClickableActor.h"

#include "NOROUTENORULE/NOROUTENORULEPlayerController.h"
#include "Objects/InteractableObject.h"

// Sets default values
AClickableActor::AClickableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
}

// Called when the game starts or when spawned
void AClickableActor::BeginPlay()
{
	Super::BeginPlay();

	if (StaticMeshComponent)
	{
		// 현재 Materials 저장
		Materials.Empty(); // 초기화
		for (int32 i = 0; i < StaticMeshComponent->GetNumMaterials(); ++i)
		{
			UMaterialInterface* Material = StaticMeshComponent->GetMaterial(i);
			Materials.Add(Material);
		}
	}
}

void AClickableActor::NotifyActorBeginCursorOver()
{
	Super::NotifyActorBeginCursorOver();
    
	if (!bIsHighlighted)
	{
		StaticMeshComponent->SetMaterial(0, OutlineMaterial);
		bIsHighlighted = true;
	}

	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		// 커서 모양을 손으로 변경
		PC->CurrentMouseCursor = EMouseCursor::Hand;
	}
}

void AClickableActor::NotifyActorEndCursorOver()
{
	Super::NotifyActorEndCursorOver();

	if (bIsHighlighted && !bIsClicked)
	{
		// Materials 복원
		for (int32 i = 0; i < Materials.Num(); ++i)
		{
			StaticMeshComponent->SetMaterial(i, Materials[i]);
		}
		
		bIsHighlighted = false;
	}

	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		// 기본 커서로 복구
		PC->CurrentMouseCursor = EMouseCursor::Default;
	}
}

void AClickableActor::NotifyActorOnClicked(FKey ButtonPressed)
{
	Super::NotifyActorOnClicked(ButtonPressed);

	Cast<ANOROUTENORULEPlayerController>(GetWorld()->GetFirstPlayerController())->W_LoadObjectWidget();
	Cast<ANOROUTENORULEPlayerController>(GetWorld()->GetFirstPlayerController())->InteractableObject->SetStaticMesh(StaticMeshComponent->GetStaticMesh(), Materials);
}
