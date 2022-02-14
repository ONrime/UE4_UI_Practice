// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IconLocation_UserWidget.generated.h"

DECLARE_DELEGATE(FIconDelegate);

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

	// ������ Ư¡
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsStatic;		// �̴ϸ��� ���̴� ���� ����(�̴ϸ��� ����� ���̰� ���� ����)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsSoundWave;	// ���̺�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsVision;		// �þ߰�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsControllerRotation;		// ��Ʈ�ѷ��� ���� ȸ��

	// ������ ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsHideIcon = false;		// ��ҿ��� �������� Ư�� ��Ȳ�� �������� �ϴ� �������ΰ��� �Ǵ�

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	// ������ �� �� //////////////////////////////////////////////////////////////////////////
	//
	// ������ ������
	void HideIcone(bool State);
	// ������ �ð� Ÿ�̸�
	FTimerHandle HiddenEndTimer;

	// ������ ���̰� �ϱ�
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Hide")
	void VisibleIcon();
	virtual void VisibleIcon_Implementation();
	// ������ ���̰� �ϱ� ������ (�ٽ� ������)
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Hide")
	void VisibleIconEnd();
	virtual void VisibleIconEnd_Implementation();

	/////////////////////////////////////////////////////////////////////////////////////////


public:

	FIconDelegate VisibleIconDelegate;



};
