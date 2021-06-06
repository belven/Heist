// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QuestObjective.generated.h"

/**
 *
 */
UCLASS()
class HEIST_API UQuestObjective : public UObject
{
	GENERATED_BODY()
protected:
	UPROPERTY()
		FString text;
public:
	UQuestObjective();

	virtual bool isComplete() { check(0 && "You must override this"); return false; };

	virtual FString getText() { check(0 && "You must override this"); return ""; };

	void setText(FString val) { text = val; }
};
