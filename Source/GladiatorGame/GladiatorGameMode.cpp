// Fill out your copyright notice in the Description page of Project Settings.


#include "GladiatorGameMode.h"

AGladiatorGameMode::AGladiatorGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawn(TEXT("/Game/Blueprints/Player/BP_Gladiator"));

	if (PlayerPawn.Class != NULL)
	{
		DefaultPawnClass = PlayerPawn.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerController(TEXT("/Game/Blueprints/Player/PC_Gladiator"));

	if (PlayerController.Class != NULL)
	{
		PlayerControllerClass = PlayerController.Class;
	}
}
