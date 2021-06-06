// Fill out your copyright notice in the Description page of Project Settings.
#include "InteractionObjective.h"
#include "HeistCharacter.h"

UInteractionObjective* UInteractionObjective::createInteractionObjective(FString inText, TArray<AInteractable*> inInteractables)
{
	UInteractionObjective* interactionObjective = NewObject<UInteractionObjective>(UInteractionObjective::StaticClass());
	interactionObjective->setText(inText);
	interactionObjective->interactables = inInteractables;

	//for (AInteractable* inteactable : inInteractables) {
	//	interactablesComplete.Add(inteactable, false);
	//}

	return interactionObjective;
}

bool UInteractionObjective::isComplete()
{
	bool complete = false;

	complete = interactablesComplete.Num() == interactables.Num();

	//for (AInteractable* inteactable : interactables) {
	//	complete&& interactablesComplete.Find(inteactable);
	//}

	return complete;
}

FString UInteractionObjective::getText()
{
	FString output = text;

	for (AInteractable* interactable : interactables) {
		output += interactable->getInteractableName() + ", ";
	}

	return output;
}

void UInteractionObjective::OnInterract(AHeistCharacter* character, AInteractable* interactable)
{
	bool found = false;

	for (AInteractable* foundInteractable : interactablesComplete) {
		if (foundInteractable == interactable) {
			found = true;
		}
	}

	if (!found)	interactablesComplete.Add(interactable);

	FString someText = getText();

	if (someText == "") {

	}
}
