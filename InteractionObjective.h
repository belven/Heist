// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestObjective.h"
#include "Interactable.h"

#include "InteractionObjective.generated.h"

class AHeistCharacter;

/**
 *
 */
UCLASS()
class HEIST_API UInteractionObjective : public UQuestObjective
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		TArray<AInteractable*> interactables;

	UPROPERTY()
		TArray<AInteractable*> interactablesComplete;
		//TMap<AInteractable*, bool > interactablesComplete;
public:
	virtual bool isComplete() override;
	virtual FString getText() override;

	void OnInterract(AHeistCharacter* character, AInteractable* interactable);

	UFUNCTION(BlueprintCallable, Category = "Interaction Objective")
		static UInteractionObjective* createInteractionObjective(FString inText, TArray<AInteractable*> inInteractables);
};
