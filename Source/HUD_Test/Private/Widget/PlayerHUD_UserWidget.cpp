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

// 플레이어가 스폰되고 미니맵이 생성 될 때 월드내의 미니맵 아이콘을 찾아 적용하는 함수입니다.
// 처음에 한번만 작동
void UPlayerHUD_UserWidget::StartMiniMap()
{
	// 월드 내에 있는 모든 액터들
	for (TActorIterator<AActor> iter(GetWorld(), AActor::StaticClass()); iter ;++iter)
	{
		AActor* temp = *iter;
		IMapIcon_Interface* IMapIcon_InterfaceIns = Cast<IMapIcon_Interface>(temp);

		// 인터페이스 인지 검사
		if (temp->GetClass()->ImplementsInterface(UMapIcon_Interface::StaticClass()))
		{
			if (Minimap_Widget)
			{
				//UE_LOG(LogTemp, Warning, TEXT("UPlayerHUD_UserWidget: StartMiniMap: %d"), (int)IMapIcon_InterfaceIns->Execute_GetIconState(temp));
				// 액터에 설정된 아이콘 상태를 가져와 미니맵에 적용합니다.
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

void UPlayerHUD_UserWidget::DelIconMiniMap(AActor* IconActor)
{
	if (Minimap_Widget)
	{
		UE_LOG(LogTemp, Warning, TEXT("DelIconMiniMap"));
		Minimap_Widget->DelDifferentIcon(IconActor);
	}
}
