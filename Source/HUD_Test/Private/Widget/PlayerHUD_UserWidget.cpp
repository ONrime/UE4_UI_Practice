// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/PlayerHUD_UserWidget.h"

void UPlayerHUD_UserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//UE_LOG(LogTemp, Warning, TEXT("UPlayerHUD_UserWidget: NativeConstruct"));
}

void UPlayerHUD_UserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	//UE_LOG(LogTemp, Warning, TEXT("UPlayerHUD_UserWidget: NativeTick"));
}
