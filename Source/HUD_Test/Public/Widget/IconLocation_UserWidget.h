// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IconLocation_UserWidget.generated.h"

/**
 * 
 */
UCLASS()
class HUD_TEST_API UIconLocation_UserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AActor* OnwerActor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMinimap_UserWidget* Minimap_Widget = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UImage* Icon_Image;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UUserWidget* Icon_Sight_Widget = nullptr;

	// 아이콘 특징
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsStatic;		// 미니맵의 보이는 범위 결정(미니맵을 벗어나도 보이게 할지 결정)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsSoundWave;	// 웨이브
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsVision;		// 시야각
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsControllerRotation;		// 컨트롤러에 따라 회전

	// 아이콘 종류
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsHiddenIcon = false;		// 평소에는 가려지고 특정 상황에 보여져야 하는 아이콘인가?

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


	void HideIcone(bool State);
	UFUNCTION()
	void HideIconEnd();

	// 타이머
	FTimerHandle HiddenEndTimer;

public:

	UFUNCTION(BlueprintCallable, Category = "Icon")
	void IconOnwerAttack(bool Set);


};
