// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Lever.generated.h"

class AHeistCharacter;

UCLASS()
class HEIST_API ALever : public AInteractable
{
	GENERATED_BODY()
public:
	ALever();
	virtual void Interact(AHeistCharacter* character) override;

	AInteractable* ObjectToSwitch() const { return objectToSwitch; }
	void ObjectToSwitch(AInteractable* val) { objectToSwitch = val; }

protected:
	UPROPERTY(EditAnywhere, Category = Lever)
		AInteractable* objectToSwitch;
};
