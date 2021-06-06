// Fill out your copyright notice in the Description page of Project Settings.
#include "Interactable.h"
#include "HeistCharacter.h"

// Sets default values
AInteractable::AInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	   
	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MechAttachment_MeshComponent"));
}

// Called when the game starts or when spawned
void AInteractable::BeginPlay()
{
	Super::BeginPlay();
}

void AInteractable::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	if (interactableMesh != nullptr)
	{
		meshComponent->SetStaticMesh(interactableMesh);
		meshComponent->SetMobility(EComponentMobility::Movable);
		meshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		//meshComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	}
}

// Called every frame
void AInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FString AInteractable::getInteractableName()
{
	return interactableName;
}
