// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD_UserWidget.generated.h"

/**
 * 
 */
UCLASS()
class HUD_TEST_API UPlayerHUD_UserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:


protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:



};
