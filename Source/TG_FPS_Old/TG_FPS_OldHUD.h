// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TG_FPS_OldHUD.generated.h"

UCLASS()
class ATG_FPS_OldHUD : public AHUD
{
	GENERATED_BODY()

public:
	ATG_FPS_OldHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

