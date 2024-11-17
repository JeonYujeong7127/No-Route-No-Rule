// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NOROUTENORULEPlayerController.generated.h"

class UInputMappingContext;

/**
 *
 */
UCLASS()
class NOROUTENORULE_API ANOROUTENORULEPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	
	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	// Begin Actor interface
protected:
	ANOROUTENORULEPlayerController();
	virtual void BeginPlay() override;
	void FindInteractableActor();
	
	UPROPERTY()
	TObjectPtr<class UInputAction> ScrollAction;
	
	UFUNCTION()
	void ZoonInOut(const FInputActionValue& Value);
	
	// End Actor interface

public:
	UPROPERTY()
	TObjectPtr<class AInteractableObject> InteractableObject;
	
	// Widget 관련 함수는 W_ 접두사 붙여 관리
	UFUNCTION()
	void W_LoadObjectWidget();

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> LoadObjectWidgetClass;

	UPROPERTY()
	TObjectPtr<UUserWidget> LoadObjectWidget;
};
