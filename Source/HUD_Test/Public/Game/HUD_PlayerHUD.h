// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUD_PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class HUD_TEST_API AHUD_PlayerHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	AHUD_PlayerHUD();

	TSubclassOf<class UPlayerHUD_UserWidget> PlayerMainUIClass;

protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaTime) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// UI
	class UPlayerHUD_UserWidget* PlayerMainUI;

	// UI
	// ¹Ì´Ï¸Ê
	TSubclassOf<class UMinimap_UserWidget> MiniMap_WidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widget)
	class UMinimap_UserWidget* Minimap_Widget;

public:

	UFUNCTION(BlueprintCallable)
	void StartMiniMap();
	UFUNCTION(BlueprintCallable)
	void UpdateMiniMap(AActor* IconActor, int IconState);
	UFUNCTION(BlueprintCallable)
	void DelIconMiniMap(AActor* IconActor);


};
