// Fill out your copyright notice in the Description page of Project Settings.


#include "HeistHud.h"
#include <CanvasItem.h>
#include "Engine/Canvas.h"

void AHeistHud::DrawHUD()
{
	Super::DrawHUD();
	//Start Point
	float xStart = 100;
	float yStart = 110;

	//DrawText(
	//	VerdanaFont, "Restart", xStart + 30, yStart + 20,
	//	LC_Black, DefaultFontScale,
	//	true, LC_Red
	//);
}

//DrawText
void AHeistHud::DrawText(
	UFont* TheFont,
	const FString& TheStr,
	const float& X, const float& Y,
	const FLinearColor& TheColor,
	const float& TheScale,
	bool DrawOutline,
	const FLinearColor OutlineColor) {
	if (!Canvas) return;

	//Text and Font
	FCanvasTextItem NewText(FVector2D(X, Y), FText::FromString(TheStr), TheFont, TheColor);

	//Text Scale
	NewText.Scale.Set(TheScale, TheScale);

	//Outline gets its alpha from the main color
	NewText.bOutlined = true;
	NewText.OutlineColor = OutlineColor;
	NewText.OutlineColor.A = TheColor.A * 2;

	//Draw
	Canvas->DrawItem(NewText);
}