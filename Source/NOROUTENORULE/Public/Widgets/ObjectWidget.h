// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ObjectWidget.generated.h"

/**
 * 
 */
UCLASS()
class NOROUTENORULE_API UObjectWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UImage> Img_Object;

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> MaterialInstanceDynamic;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterial> ChromaKeyMaterial;
	
	virtual void NativeConstruct() override;
};
