// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/HUD_PlayerHUD.h"
#include "Widget/PlayerHUD_UserWidget.h"
#include "Widget/Minimap_UserWidget.h"
#include "Interface/MapIcon_Interface.h"
#include "EngineUtils.h"

AHUD_PlayerHUD::AHUD_PlayerHUD()
{
	// 미니맵
	static ConstructorHelpers::FClassFinder<UMinimap_UserWidget>MINIMAPWIDGET(TEXT("WidgetBlueprint'/Game/UI/Minimap/Widget/Minimap_Widget.Minimap_Widget_c'"));
	if (MINIMAPWIDGET.Succeeded()) MiniMap_WidgetClass = MINIMAPWIDGET.Class;

	Minimap_Widget = CreateWidget<UMinimap_UserWidget>(GetWorld(), MiniMap_WidgetClass);
	
}

void AHUD_PlayerHUD::BeginPlay()
{
	Super::BeginPlay();

	if (Minimap_Widget)
	{
		Minimap_Widget->AddToViewport();
	}
}

void AHUD_PlayerHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();


}

void AHUD_PlayerHUD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void AHUD_PlayerHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);


}

// 플레이어가 스폰되고 미니맵이 생성 될 때 월드내의 미니맵 아이콘을 찾아 적용하는 함수입니다.
// 처음에 한번만 작동
void AHUD_PlayerHUD::StartMiniMap()
{
	// 월드 내에 있는 모든 액터들
	for (TActorIterator<AActor> iter(GetWorld(), AActor::StaticClass()); iter; ++iter)
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

// 플레이가 진행될 때 미니맵에 아이콘이 추가되면 작동되는 함수입니다.
// 미니맵에 새로운 아이콘을 추가합니다.
void AHUD_PlayerHUD::UpdateMiniMap(AActor* IconActor, int IconState)
{
	UE_LOG(LogTemp, Warning, TEXT("UpdateMiniMap: %d"), (int)IconState);
	if (Minimap_Widget)
	{
		if ((EMapIconState)IconState == EMapIconState::PLACE) UE_LOG(LogTemp, Warning, TEXT("UPlayerHUD_UserWidget: UpdateMiniMap: %d"), (int)IconState);
		Minimap_Widget->AddDifferentIcon(IconActor, (EMapIconState)IconState);
	}
}

// 플레이 도중 미니맵에 있는 아이콘이 삭제 될 때 작동되는 함수입니다.
void AHUD_PlayerHUD::DelIconMiniMap(AActor* IconActor)
{
	if (Minimap_Widget)
	{
		UE_LOG(LogTemp, Warning, TEXT("DelIconMiniMap"));
		Minimap_Widget->DelDifferentIcon(IconActor);
	}
}

