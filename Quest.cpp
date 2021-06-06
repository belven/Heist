// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest.h"
#include "QuestReward.h"

UQuest::UQuest() : Super()
{

}

UQuest* UQuest::CreateQuest(int32 inID, FString inName, TArray<UQuestObjective*> inObjectives, TArray<UQuestReward*> inRewards)
{
	UQuest* quest = NewObject<UQuest>(UQuest::StaticClass());
	quest->id = inID;
	quest->questName = inName;
	quest->objectives = inObjectives;
	quest->rewards = inRewards;
	return quest;
}

bool UQuest::isComplete()
{
	bool complete = false;

	for (UQuestObjective* qo : getObjectives()) {
		complete && qo->isComplete();
	}

	return complete;
}

FString UQuest::getText()
{
	FString text = questName;

	for (UQuestObjective* qo : getObjectives()) {
		text += qo->getText();
	}

	return text;
}
