// Copyright Epic Games, Inc. All Rights Reserved.

#include "Game/HUD_TestGameMode.h"
#include "Player/HUD_TestCharacter.h"
#include "Game/HUD_PlayerHUD.h"
#include "UObject/ConstructorHelpers.h"

AHUD_TestGameMode::AHUD_TestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = AHUD_TestCharacter::StaticClass();
		HUDClass = AHUD_PlayerHUD::StaticClass();
	}

}
