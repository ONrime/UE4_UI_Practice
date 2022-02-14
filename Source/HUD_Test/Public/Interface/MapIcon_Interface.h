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
 * 맵에서 작동 될 아이콘이 필요한 액터에 추가 되는 인터페이스입니다.
 * 아이콘의 상태를 나타내 줄 EMapIconState의 변수를 만들어 주어야 합니다.
 * 아이콘과 직접적인 연결이 되어야 함으로 아이콘 위젯 변수(포인터)를 만들어 주어야 합니다.
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

	// 액터의 아이콘 상태를 전달하기 위해 필요한 함수입니다.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MapIcon")
	EMapIconState GetIconState();

	// 아이콘과 액터 연결하기
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MapIcon")
	void SetIconWidget(class UUserWidget* Set);

	// 아이콘과 액터 연결하기
	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MapIcon")
	//class UUserWidget* GetIconLocationWidget();

	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MapIcon")
	//void UpdateIcon(EMapIconState Set);

protected:
	//class UIconLocation_UserWidget* IconLocation_Widget = nullptr;

};
