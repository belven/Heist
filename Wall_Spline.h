// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "Wall_Spline.generated.h"

UCLASS(Blueprintable)
class HEIST_API AWall_Spline : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWall_Spline();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

	USplineComponent* splincomp;
	UStaticMesh* wallMesh;

	UPROPERTY(EditAnywhere, Category = Spline)
	TMap<int32, UStaticMesh*> meshVarients;	
};
