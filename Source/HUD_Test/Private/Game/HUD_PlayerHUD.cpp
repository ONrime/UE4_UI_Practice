// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/HUD_PlayerHUD.h"
#include "Widget/PlayerHUD_UserWidget.h"
#include "Widget/Minimap_UserWidget.h"
#include "Interface/MapIcon_Interface.h"
#include "EngineUtils.h"

AHUD_PlayerHUD::AHUD_PlayerHUD()
{
	// �̴ϸ�
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

// �÷��̾ �����ǰ� �̴ϸ��� ���� �� �� ���峻�� �̴ϸ� �������� ã�� �����ϴ� �Լ��Դϴ�.
// ó���� �ѹ��� �۵�
void AHUD_PlayerHUD::StartMiniMap()
{
	// ���� ���� �ִ� ��� ���͵�
	for (TActorIterator<AActor> iter(GetWorld(), AActor::StaticClass()); iter; ++iter)
	{
		AActor* temp = *iter;
		IMapIcon_Interface* IMapIcon_InterfaceIns = Cast<IMapIcon_Interface>(temp);

		// �������̽� ���� �˻�
		if (temp->GetClass()->ImplementsInterface(UMapIcon_Interface::StaticClass()))
		{
			if (Minimap_Widget)
			{
				//UE_LOG(LogTemp, Warning, TEXT("UPlayerHUD_UserWidget: StartMiniMap: %d"), (int)IMapIcon_InterfaceIns->Execute_GetIconState(temp));
				// ���Ϳ� ������ ������ ���¸� ������ �̴ϸʿ� �����մϴ�.
				Minimap_Widget->AddDifferentIcon(temp, IMapIcon_InterfaceIns->Execute_GetIconState(temp));
			}
		}
	}
}

// �÷��̰� ����� �� �̴ϸʿ� �������� �߰��Ǹ� �۵��Ǵ� �Լ��Դϴ�.
// �̴ϸʿ� ���ο� �������� �߰��մϴ�.
void AHUD_PlayerHUD::UpdateMiniMap(AActor* IconActor, int IconState)
{
	UE_LOG(LogTemp, Warning, TEXT("UpdateMiniMap: %d"), (int)IconState);
	if (Minimap_Widget)
	{
		if ((EMapIconState)IconState == EMapIconState::PLACE) UE_LOG(LogTemp, Warning, TEXT("UPlayerHUD_UserWidget: UpdateMiniMap: %d"), (int)IconState);
		Minimap_Widget->AddDifferentIcon(IconActor, (EMapIconState)IconState);
	}
}

// �÷��� ���� �̴ϸʿ� �ִ� �������� ���� �� �� �۵��Ǵ� �Լ��Դϴ�.
void AHUD_PlayerHUD::DelIconMiniMap(AActor* IconActor)
{
	if (Minimap_Widget)
	{
		UE_LOG(LogTemp, Warning, TEXT("DelIconMiniMap"));
		Minimap_Widget->DelDifferentIcon(IconActor);
	}
}

