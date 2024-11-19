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
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UTextBlock> TB_BlinkText;

private:
	virtual void HandleSpacebarPress();
	virtual void ToggleBlink();

	FTimerHandle BlinkTimerHandle;
};
