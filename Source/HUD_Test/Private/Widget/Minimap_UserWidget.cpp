// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Minimap_UserWidget.h"
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"

void UMinimap_UserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 초기화
	UMaterialParameterCollection* ParameterCollection = nullptr;
	Map_ParameterCollection = nullptr;

	// 파라미터 컬렉션 찾기
	ParameterCollection = LoadObject<UMaterialParameterCollection>(nullptr, TEXT("MaterialParameterCollection'/Game/UI/Minimap/Minimap_Data.Minimap_Data'"));
	
	// 찾은 파라미터 컬렉션에서 설정 부여하기
	if(ParameterCollection) Map_ParameterCollection = GetWorld()->GetParameterCollectionInstance(ParameterCollection);

	if (Map_ParameterCollection)
	{
		Map_ParameterCollection->SetScalarParameterValue("Dimensions", Map_Dimensions);
		Map_ParameterCollection->SetScalarParameterValue("Zoom", Map_Zoom);
	}
}

void UMinimap_UserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (Map_ParameterCollection)
	{
		// 플레이어의 위치에 따라 이미지의 UVs(좌표)가 움직이게 하기
		FVector PlayerLoc = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
		Map_ParameterCollection->SetScalarParameterValue("X", PlayerLoc.X);
		Map_ParameterCollection->SetScalarParameterValue("Y", PlayerLoc.Y);

		// 줌 설정
		Map_ParameterCollection->SetScalarParameterValue("Zoom", Map_Zoom);
	}
}
