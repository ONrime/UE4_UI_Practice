// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/PlayerHUD_UserWidget.h"
#include "Widget/Minimap_UserWidget.h"
#include "EngineUtils.h"


void UPlayerHUD_UserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//UE_LOG(LogTemp, Warning, TEXT("UPlayerHUD_UserWidget: NativeConstruct"));

	/*StartMiniMapEvent.BindLambda([this]()->void
	{ // 플레이어가 시작되면서 기존의 월드에 있는 오브젝트를 미니맵에 표시합니다.
		StartMiniMap();
	});*/

	/*UpdateMinimapEvent.BindLambda([this](AActor* IconActor, int State)->void
	{ // 플레이어가 시작되면서 기존의 월드에 있는 오브젝트를 미니맵에 표시합니다.
		UpdateMiniMap(IconActor, State);
	});*/

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
		IMapIcon_Interface* IMapIcon_InterfaceIns = Cast<IMapIcon_Interface>(temp);
		//if (IMapIcon_InterfaceIns && IMapIcon_InterfaceIns->Execute_GetIconState(temp) != EMapIconState::PLAYER)
		if (IMapIcon_InterfaceIns)
		{
			if (Minimap_Widget)
			{
				UE_LOG(LogTemp, Warning, TEXT("UPlayerHUD_UserWidget: StartMiniMap: %d"), (int)IMapIcon_InterfaceIns->Execute_GetIconState(temp));
				Minimap_Widget->AddDifferentIcon(temp, IMapIcon_InterfaceIns->Execute_GetIconState(temp));
			}
		}
	}
}

void UPlayerHUD_UserWidget::UpdateMiniMap(AActor* IconActor, EMapIconState IconState)
{
	UE_LOG(LogTemp, Warning, TEXT("UpdateMiniMap: %d"), (int)IconState);
	if (Minimap_Widget)
	{
		if(IconState == EMapIconState::PLACE) UE_LOG(LogTemp, Warning, TEXT("UPlayerHUD_UserWidget: UpdateMiniMap: %d"), (int)IconState);
		Minimap_Widget->AddDifferentIcon(IconActor, IconState);
	}
}
