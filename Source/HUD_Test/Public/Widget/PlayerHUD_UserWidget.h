// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD_UserWidget.generated.h"

/**
 * 
 */

DECLARE_DELEGATE(FPlayerHUDDelegate);
//DECLARE_DELEGATE_OneParam(FPlayerHUDActorDelegate, AActor*)
DECLARE_DELEGATE_TwoParams(FPlayerHUDActorDelegate, AActor*, int)
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPlayerHUDActorDelegate, AActor*, IconActor, int, IconState);

UCLASS()
class HUD_TEST_API UPlayerHUD_UserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	FPlayerHUDDelegate StartMiniMapEvent;
	//UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
	FPlayerHUDActorDelegate UpdateMinimapEvent;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void StartMiniMap();
	void UpdateMiniMap(AActor* Actor, int State);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widget)
	class UMinimap_UserWidget* Minimap_Widget;

private:



};
