// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interactable.h"
#include "Quest.h"
#include "HeistPlayerController.generated.h"

#define mCharacterCollision ECollisionChannel::ECC_Pawn

UCLASS()
class AHeistPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AHeistPlayerController();

protected:
	void createQuest();

	UPROPERTY()
		UQuest* quest;

	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// End PlayerController interface

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	void Interact();
	void CalculateQuests(AInteractable* interactable);
	FHitResult GetHitFromCursor(ECollisionChannel channel = mCharacterCollision);

	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();

	/** Navigate player to the current touch location. */
	void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();
};


