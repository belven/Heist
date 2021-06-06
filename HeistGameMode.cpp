// Copyright Epic Games, Inc. All Rights Reserved.

#include "HeistGameMode.h"
#include "HeistPlayerController.h"
#include "HeistCharacter.h"
#include "HeistHud.h"
#include "UObject/ConstructorHelpers.h"

AHeistGameMode::AHeistGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AHeistPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	HUDClass = AHeistHud::StaticClass();
}