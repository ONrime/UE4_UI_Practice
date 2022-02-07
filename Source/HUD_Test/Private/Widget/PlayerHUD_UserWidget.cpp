// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/PlayerHUD_UserWidget.h"
#include "Widget/Minimap_UserWidget.h"
#include "Interface/MapIcon_Interface.h"
#include "EngineUtils.h"


void UPlayerHUD_UserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//UE_LOG(LogTemp, Warning, TEXT("UPlayerHUD_UserWidget: NativeConstruct"));

	StartMiniMapEvent.BindLambda([this]()->void
	{ // �÷��̾ ���۵Ǹ鼭 ������ ���忡 �ִ� ������Ʈ�� �̴ϸʿ� ǥ���մϴ�.
		StartMiniMap();
	});

	UpdateMinimapEvent.BindLambda([this](AActor* IconActor, int State)->void
	{ // �÷��̾ ���۵Ǹ鼭 ������ ���忡 �ִ� ������Ʈ�� �̴ϸʿ� ǥ���մϴ�.
		UpdateMiniMap(IconActor, State);
	});

	//UpdateMinimapEvent.AddDynamic(this, &UPlayerHUD_UserWidget::UpdateMiniMap);

}

void UPlayerHUD_UserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	//UE_LOG(LogTemp, Warning, TEXT("UPlayerHUD_UserWidget: NativeTick"));
}

void UPlayerHUD_UserWidget::StartMiniMap()
{
	for (TActorIterator<AActor> iter(GetWorld(), AActor::StaticClass()); iter ;++iter)
	{
		AActor* temp = *iter;
		IMapIcon_Interface* IMapIcon_InterfaceIns = Cast< IMapIcon_Interface>(temp);

		if (IMapIcon_InterfaceIns && IMapIcon_InterfaceIns->IconState == EMapIconState::ALLIANCE)
		{
			if (Minimap_Widget)
			{
				Minimap_Widget->AddDifferentIcon(temp, IMapIcon_InterfaceIns->IconState);
			}
		}
	}
}

void UPlayerHUD_UserWidget::UpdateMiniMap(AActor* Actor, int State)
{
	if (Minimap_Widget)
	{
		Minimap_Widget->AddDifferentIcon(Actor, (EMapIconState)State);
	}
}
