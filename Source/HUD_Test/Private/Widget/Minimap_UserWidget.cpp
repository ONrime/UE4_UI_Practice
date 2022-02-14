// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Minimap_UserWidget.h"
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"
#include "Interface/MapIcon_Interface.h"
#include "EngineUtils.h"

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

// ���ο� ������ �߰�
void UMinimap_UserWidget::AddDifferentIcon_Implementation(AActor* Actor, EMapIconState State)
{
	//UE_LOG(LogTemp, Warning, TEXT("AddDifferentIcon_Implementation"));
	/*if (Actor)
	{
		IMapIcon_Interface* Icon_Actor = Cast<IMapIcon_Interface>(Actor);
		
		// �������̽� ���� �˻�
		if (Actor->GetClass()->ImplementsInterface(UMapIcon_Interface::StaticClass()))
		{
			if(Icon_Actor) Icon_Actor->SetIconLocationWidget(this);
		}
	}*/
}

// ������ ����
void UMinimap_UserWidget::DelDifferentIcon_Implementation(AActor* Actor)
{
	/*UE_LOG(LogTemp, Warning, TEXT("DelDifferentIcon_Implementation"));
	if (Map_Icons.Num() > 0)
	{
		UIconLocation_UserWidget* DelIcon = nullptr;
		for (UIconLocation_UserWidget* Icon : Map_Icons)
		{
			if (Icon->OnwerActor == Actor)
			{
				UE_LOG(LogTemp, Warning, TEXT("DelDifferentIcon_Implementation: find"));
				DelIcon = Icon;
				break;
			}
		}
		UE_LOG(LogTemp, Warning, TEXT("DelDifferentIcon_Implementation: del"));
		DelIcon->RemoveFromParent();

	}*/
}
