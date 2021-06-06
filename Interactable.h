// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.generated.h"

class AHeistCharacter;

UCLASS()
class HEIST_API AInteractable : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractable();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(EditAnywhere, Category = Interactable)
		UStaticMesh* interactableMesh;

	UPROPERTY(EditAnywhere, Category = Interactable)
		UStaticMeshComponent* meshComponent = nullptr;

	UPROPERTY(EditAnywhere, Category = Interactable)
		FString interactableName;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FString getInteractableName();

	UFUNCTION(BlueprintCallable, Category = "Interactable")
		virtual void Interact(AHeistCharacter* character) { check(0 && "You must override this"); };
};