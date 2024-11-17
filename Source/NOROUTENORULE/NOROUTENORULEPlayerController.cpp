// Copyright Epic Games, Inc. All Rights Reserved.


#include "NOROUTENORULEPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Objects/InteractableObject.h"

ANOROUTENORULEPlayerController::ANOROUTENORULEPlayerController()
{
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_Scroll(TEXT("/Game/FirstPerson/Input/Actions/IA_Scroll.IA_Scroll"));
	if (IA_Scroll.Succeeded())
	{
		ScrollAction = IA_Scroll.Object;
	}
}

void ANOROUTENORULEPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;
	bEnableMouseOverEvents = true;
	bEnableClickEvents = true;
	
	// 입력 모드를 게임 전용으로 설정
	SetInputMode(FInputModeGameAndUI());

	// InteractableActor 찾아 포인터에 바인딩 
	FindInteractableActor();
	
	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
	
	if (TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(ScrollAction, ETriggerEvent::Triggered, this, &ANOROUTENORULEPlayerController::ZoonInOut);
	}
}

void ANOROUTENORULEPlayerController::FindInteractableActor()
{
	TArray<AActor*> FoundActors;
	
	// 현재 레벨에서 AMyActor 인스턴스를 모두 찾아 배열에 저장
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AInteractableObject::StaticClass(), FoundActors);

	if (FoundActors.Num() > 0)
	{
		if (Cast<AInteractableObject>(FoundActors[0]))
		{
			InteractableObject = Cast<AInteractableObject>(FoundActors[0]);
			UE_LOG(LogTemp, Log, TEXT("Found AMyActor instance: %s"), *InteractableObject->GetName());
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No AMyActor instance found in the level"));
	}
}

void ANOROUTENORULEPlayerController::ZoonInOut(const FInputActionValue& Value)
{
	float _Value = Value.Get<float>();
	InteractableObject->ZoonInOut(_Value);
}

void ANOROUTENORULEPlayerController::W_LoadObjectWidget()
{
	if(LoadObjectWidget)
	{
		LoadObjectWidget->AddToViewport();
	}
	else if(LoadObjectWidgetClass)
	{
		LoadObjectWidget = CreateWidget(GetWorld(), LoadObjectWidgetClass);
		if(LoadObjectWidget)
		{
			LoadObjectWidget->AddToViewport();
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("There is No ObjectWidget and class"));
	}
}
