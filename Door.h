// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Door.generated.h"

class AHeistCharacter;

UCLASS()
class HEIST_API ADoor : public AInteractable
{
	GENERATED_BODY()
private:
	bool open = false;
public:
	ADoor();
	virtual void Interact(AHeistCharacter* character) override;


	UPROPERTY(EditAnywhere, Category = Character)
		int32 doorAngle = 0;
};
