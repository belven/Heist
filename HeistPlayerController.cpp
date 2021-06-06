// Copyright Epic Games, Inc. All Rights Reserved.

#include "HeistPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "HeistCharacter.h"
#include "Engine/World.h"
#include "InteractionObjective.h"
#include "QuestObjective.h"
#include "Quest.h"
#include "InteractionObjective.h"
#include <EngineUtils.h>

AHeistPlayerController::AHeistPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AHeistPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}

void AHeistPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AHeistPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AHeistPlayerController::OnSetDestinationReleased);

	InputComponent->BindAction("Interact", IE_Released, this, &AHeistPlayerController::Interact);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AHeistPlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AHeistPlayerController::MoveToTouchLocation);

	InputComponent->BindAction("ResetVR", IE_Pressed, this, &AHeistPlayerController::OnResetVR);
}

void AHeistPlayerController::BeginPlay()
{
	Super::BeginPlay();
	createQuest();
}

void AHeistPlayerController::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AHeistPlayerController::Interact()
{
	FHitResult Hit = GetHitFromCursor();

	if (Hit.bBlockingHit)
	{
		if (Hit.GetActor() != nullptr) {
			AInteractable* interactable = Cast<AInteractable>(Hit.Actor);

			if (interactable != nullptr) {
				interactable->Interact(Cast<AHeistCharacter>(GetOwner()));

				CalculateQuests(interactable);
			}
		}
	}
}


void AHeistPlayerController::createQuest()
{
	TArray<UQuestObjective*> objectives;
	TArray<UQuestReward*> rewards;

	TArray<AInteractable*> interactables;


	for (TActorIterator<AInteractable> interactable(GetWorld()); interactable; ++interactable)
	{
		interactables.Add(*interactable);
	}

	objectives.Add(UInteractionObjective::createInteractionObjective("Interact with ", interactables));

	quest = UQuest::CreateQuest(1, "Test", objectives, rewards);
}

void AHeistPlayerController::CalculateQuests(AInteractable* interactable) {
	if (quest != nullptr) {
		for (UQuestObjective* qo : quest->getObjectives())
		{
			if (qo->GetClass()->IsChildOf(UInteractionObjective::StaticClass())) {
				UInteractionObjective* io = Cast<UInteractionObjective>(qo);
				io->OnInterract(Cast<AHeistCharacter>(GetOwner()), interactable);
			}
		}
	}

}


FHitResult AHeistPlayerController::GetHitFromCursor(ECollisionChannel channel)
{
	static FHitResult Hit;
	GetHitResultUnderCursor(channel, true, Hit);
	return Hit;
}

void AHeistPlayerController::MoveToMouseCursor()
{
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		if (AHeistCharacter* MyPawn = Cast<AHeistCharacter>(GetPawn()))
		{
			if (MyPawn->GetCursorToWorld())
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MyPawn->GetCursorToWorld()->GetComponentLocation());
			}
		}
	}
	else
	{
		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit)
		{
			// We hit something, move there
			SetNewMoveDestination(Hit.ImpactPoint);
		}
	}
}

void AHeistPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void AHeistPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
			
		}
	}
}

void AHeistPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void AHeistPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}