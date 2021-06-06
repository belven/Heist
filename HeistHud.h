// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HeistHud.generated.h"

/**
 *
 */
UCLASS()
class HEIST_API AHeistHud : public AHUD
{
	GENERATED_BODY()
public:
	virtual void DrawHUD() override;
	void DrawText(UFont* TheFont, const FString& TheStr, const float& X, const float& Y, const FLinearColor& TheColor, 
		const float& TheScale, bool DrawOutline = false, const FLinearColor OutlineColor = FLinearColor(0, 0, 0, 1));
};
