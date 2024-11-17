// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ObjectWidget.h"

void UObjectWidget::NativeConstruct()
{
	Super::NativeConstruct();

	MaterialInstanceDynamic = UMaterialInstanceDynamic::Create(ChromaKeyMaterial, this);
}
