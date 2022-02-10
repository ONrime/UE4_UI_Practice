// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interface/MapIcon_Interface.h"
#include "Minimap_UserWidget.generated.h"

/**
 * 위젯에서는 ConstructorHelpers가 아닌 LoadObject를 사용하자
 */
UCLASS()
class HUD_TEST_API UMinimap_UserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	class UTexture* Map_Image;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	float Map_Zoom;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	float Map_Dimensions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	class UMaterialInstance* Map_Instance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	TArray<class UIconLocation_UserWidget*> Map_Icons;

	// 미니맵에 아이콘 추가
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MapIcon")
	void AddDifferentIcon(AActor* Actor, EMapIconState State);
	virtual void AddDifferentIcon_Implementation(AActor* Actor, EMapIconState State);

	// 미니맵에 아이콘 삭제
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MapIcon")
	void DelDifferentIcon(AActor* Actor);
	virtual void DelDifferentIcon_Implementation(AActor* Actor);

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY()
	class UMaterialParameterCollectionInstance* Map_ParameterCollection;

	//TSubclassOf<class UIconLocation_UserWidget> AllianceLocation_WidgetClass;
	//TSubclassOf<class UIconLocation_UserWidget> EnemyLocation_WidgetClass;

private:



};
