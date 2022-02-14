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
 * �ʿ��� �۵� �� �������� �ʿ��� ���Ϳ� �߰� �Ǵ� �������̽��Դϴ�.
 * �������� ���¸� ��Ÿ�� �� EMapIconState�� ������ ����� �־�� �մϴ�.
 * �����ܰ� �������� ������ �Ǿ�� ������ ������ ���� ����(������)�� ����� �־�� �մϴ�.
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

	// �÷��̾� �������� ���� �� �� ������ ã��
	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MapIcon")
	//void StartIcon(EMapIconState Set);

	// ������ ������ ���¸� �����ϱ� ���� �ʿ��� �Լ��Դϴ�.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MapIcon")
	EMapIconState GetIconState();

	// �����ܰ� ���� �����ϱ�
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MapIcon")
	void SetIconWidget(class UUserWidget* Set);

	// �����ܰ� ���� �����ϱ�
	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MapIcon")
	//class UUserWidget* GetIconLocationWidget();

	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MapIcon")
	//void UpdateIcon(EMapIconState Set);

protected:
	//class UIconLocation_UserWidget* IconLocation_Widget = nullptr;

};
