// Fill out your copyright notice in the Description page of Project Settings.


#include "Wall_Spline.h"
#include "Components/SplineMeshComponent.h"

// Sets default values
AWall_Spline::AWall_Spline()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	splincomp = CreateDefaultSubobject<USplineComponent>(TEXT("Wall_Spline"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> wall(TEXT("StaticMesh'/Game/TopDownCPP/Blueprints/Models/Objects/Wall.Wall'"));

	if (wall.Succeeded())
	{
		wallMesh = wall.Object;
	}

	SetRootComponent(splincomp);
} 

void AWall_Spline::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	ESplineCoordinateSpace::Type local = ESplineCoordinateSpace::Local;

	if (splincomp != nullptr) {
		for (int i = 0; i < splincomp->GetNumberOfSplinePoints() - 1; i++) {
			USplineMeshComponent* newComp = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass());
			newComp->CreationMethod = EComponentCreationMethod::UserConstructionScript;

			if (meshVarients.Find(i) != nullptr) {
				newComp->SetStaticMesh(meshVarients[i]);
			} else {
				newComp->SetStaticMesh(wallMesh);
			}

			newComp->SetForwardAxis(ESplineMeshAxis::X);
			newComp->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
			newComp->SetMobility(EComponentMobility::Movable);

			newComp->AttachToComponent(splincomp, FAttachmentTransformRules::KeepRelativeTransform);
			newComp->RegisterComponentWithWorld(GetWorld());
			
			const FVector startpos = splincomp->GetLocationAtSplinePoint(i, local);
			const FVector starttangent = splincomp->GetTangentAtSplinePoint(i, local);

			const FVector endpos = splincomp->GetLocationAtSplinePoint(i + 1, local);
			const FVector endtangent = splincomp->GetTangentAtSplinePoint(i + 1, local);

			newComp->SetStartAndEnd(startpos, starttangent, endpos, endtangent, true);
		}
	}
}