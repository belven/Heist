// Fill out your copyright notice in the Description page of Project Settings.

#include "Lever.h"
#include "HeistCharacter.h"

ALever::ALever() : Super()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> lever(TEXT("StaticMesh'/Game/TopDownCPP/Blueprints/Models/Objects/Lever_Static.Lever_Static'"));

	if (lever.Succeeded())
	{
		interactableMesh = lever.Object;
	}
}

void ALever::Interact(AHeistCharacter* character)
{
	if (objectToSwitch != nullptr) {
		objectToSwitch->Interact(character);
	}
}
