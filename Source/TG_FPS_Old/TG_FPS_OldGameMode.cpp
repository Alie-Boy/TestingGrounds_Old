// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "TG_FPS_OldGameMode.h"
#include "TG_FPS_OldHUD.h"
#include "Player/FirstPersonCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATG_FPS_OldGameMode::ATG_FPS_OldGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Player/Behaviour/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ATG_FPS_OldHUD::StaticClass();
}
