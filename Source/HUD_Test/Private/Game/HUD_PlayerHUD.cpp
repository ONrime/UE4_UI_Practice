// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/HUD_PlayerHUD.h"
#include "Widget/PlayerHUD_UserWidget.h"
#include "EngineUtils.h"

AHUD_PlayerHUD::AHUD_PlayerHUD()
{
	// UI
	static ConstructorHelpers::FClassFinder<UUserWidget>PLAYERHUD_WIDGET(TEXT("WidgetBlueprint'/Game/UI/Player_HUD_Widget.Player_HUD_Widget_c'"));
	if (PLAYERHUD_WIDGET.Succeeded()) PlayerMainUIClass = PLAYERHUD_WIDGET.Class;

	PlayerMainUI = CreateWidget<UPlayerHUD_UserWidget>(GetWorld(), PlayerMainUIClass);
}

void AHUD_PlayerHUD::BeginPlay()
{
	Super::BeginPlay();

	//PlayerMainUI = CreateWidget<UPlayerHUD_UserWidget>(GetWorld(), PlayerMainUIClass);
	if (PlayerMainUI)
	{
		//UE_LOG(LogTemp, Warning, TEXT("AHUD_PlayerHUD: BeginPlay"));
		PlayerMainUI->AddToViewport();
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

void AHUD_PlayerHUD::StartMiniMap()
{
	//PlayerMainUI->StartMiniMapEvent.Execute();
	PlayerMainUI->StartMiniMap();
}

void AHUD_PlayerHUD::UpdateMiniMap(AActor* IconActor, int IconState)
{
	if (PlayerMainUI)
	{
		PlayerMainUI->UpdateMiniMap(IconActor, (EMapIconState)IconState);
	}
}

void AHUD_PlayerHUD::DelIconMiniMap(AActor* IconActor)
{
	if (PlayerMainUI)
	{
		PlayerMainUI->DelIconMiniMap(IconActor);
	}
}

