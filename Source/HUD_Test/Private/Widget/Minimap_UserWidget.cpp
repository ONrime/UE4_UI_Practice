// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Minimap_UserWidget.h"
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"

void UMinimap_UserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// �ʱ�ȭ
	UMaterialParameterCollection* ParameterCollection = nullptr;
	Map_ParameterCollection = nullptr;

	// �Ķ���� �÷��� ã��
	ParameterCollection = LoadObject<UMaterialParameterCollection>(nullptr, TEXT("MaterialParameterCollection'/Game/UI/Minimap/Minimap_Data.Minimap_Data'"));
	
	// ã�� �Ķ���� �÷��ǿ��� ���� �ο��ϱ�
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
		// �÷��̾��� ��ġ�� ���� �̹����� UVs(��ǥ)�� �����̰� �ϱ�
		FVector PlayerLoc = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
		Map_ParameterCollection->SetScalarParameterValue("X", PlayerLoc.X);
		Map_ParameterCollection->SetScalarParameterValue("Y", PlayerLoc.Y);

		// �� ����
		Map_ParameterCollection->SetScalarParameterValue("Zoom", Map_Zoom);
	}
}
