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

	/*UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MapIcon")
	void AddMapIcon();
	virtual void AddMapIcon_Implementation() override;*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AActor* OnwerActor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMinimap_UserWidget* Minimap_Widget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UImage* Icon_Image;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsStatic;		// 미니맵의 보이는 범위 결정(미니맵을 벗어나도 보이게 할지 결정)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsSoundWave;	// 웨이브
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsVision;		// 시야각

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

};
