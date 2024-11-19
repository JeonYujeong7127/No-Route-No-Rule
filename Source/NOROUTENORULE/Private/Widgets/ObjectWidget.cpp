// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ObjectWidget.h"

#include "Components/TextBlock.h"

void UObjectWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
	GetWorld()->GetFirstPlayerController()->InputComponent->BindKey(EKeys::SpaceBar, IE_Pressed, this, &UObjectWidget::HandleSpacebarPress);
	
	// 타이머를 설정해 깜빡이는 함수 반복 실행
	GetWorld()->GetTimerManager().SetTimer(BlinkTimerHandle, this, &UObjectWidget::ToggleBlink, 0.5f, true);
}

void UObjectWidget::NativeDestruct()
{
	Super::NativeDestruct();
	
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	GetWorld()->GetTimerManager().ClearTimer(BlinkTimerHandle);
}

void UObjectWidget::ToggleBlink()
{
	if (TB_BlinkText)
	{
		FSlateColor CurrentSColor = TB_BlinkText->GetColorAndOpacity();
		FLinearColor CurrentLColor = CurrentSColor.GetSpecifiedColor();
		float CurrentOpacity = CurrentLColor.A;
		float NewOpacity = (CurrentOpacity > 0.5f) ? 0.0f : 1.0f;

		UE_LOG(LogTemp, Log, TEXT("CurrentOpacity: %f, NewOpacity: %f"), CurrentOpacity, NewOpacity);

		TB_BlinkText->SetOpacity(NewOpacity);
	}
}

void UObjectWidget::HandleSpacebarPress()
{
	// UI 제거
	RemoveFromParent();
}
