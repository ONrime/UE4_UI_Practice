// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MapIcon_Interface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMapIcon_Interface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */

UENUM(BlueprintType)
enum class EMapIconState : uint8 
{
	ENEMY UMETA(DisplayName = "Enemy"),
	PLAYER UMETA(DisplayName = "Player"),
	ALLIANCE UMETA(DisplayName = "Alliance"),
	PLACE UMETA(DisplayName = "Place"),
	TARGET UMETA(DisplayName = "Target")
};

class HUD_TEST_API IMapIcon_Interface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	// 플레이어 기준으로 시작 할 때 아이콘 찾기
	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MapIcon")
	//void StartIcon(EMapIconState Set);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MapIcon")
	EMapIconState GetIconState();

	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MapIcon")
	//void UpdateIcon(EMapIconState Set);

	EMapIconState IconState;

};
