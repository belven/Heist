// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QuestObjective.h"
#include "Quest.generated.h"

class UQuestReward;

/**
 *
 */
UCLASS()
class HEIST_API UQuest : public UObject
{
	GENERATED_BODY()
protected:
	UPROPERTY()
		int32 id;

	UPROPERTY()
		FString questName;

	UPROPERTY()
		TArray<UQuestObjective*> objectives;

	UPROPERTY()
		TArray<UQuestReward*> rewards;
public:
	UQuest();

	UFUNCTION(BlueprintCallable, Category = "Quest")
		static UQuest* CreateQuest(int32 inID, FString inName, TArray<UQuestObjective*> inObjectives, TArray<UQuestReward*> inRewards);

	UFUNCTION(BlueprintCallable, Category = "Quest")
		bool isComplete();

	UFUNCTION(BlueprintCallable, Category = "Quest")
		TArray<UQuestObjective*>& getObjectives() { return objectives; }

	UFUNCTION(BlueprintCallable, Category = "Quest")
		TArray<UQuestReward*>& getRewards() { return rewards; }

	UFUNCTION(BlueprintCallable, Category = "Quest")
		FString getText();
};
