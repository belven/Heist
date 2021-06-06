// Fill out your copyright notice in the Description page of Project Settings.

#include "Door.h"
#include "HeistCharacter.h"

ADoor::ADoor() : Super()
{
	// StaticMesh'/Game/TopDownCPP/Blueprints/Models/Objects/Door.Door'

	static ConstructorHelpers::FObjectFinder<UStaticMesh> door(TEXT("StaticMesh'/Game/TopDownCPP/Blueprints/Models/Objects/Door.Door'"));

	if (door.Succeeded())
	{
		interactableMesh = door.Object;
	}
}

void ADoor::Interact(AHeistCharacter* character)
{
	// Open the door
	if (!open) {
		SetActorRotation(FRotator(0, 180, 0));
		open = true;
	}
	// Close the door
	else {
		SetActorRotation(FRotator(0, doorAngle, 0));
		open = false;
	}
}