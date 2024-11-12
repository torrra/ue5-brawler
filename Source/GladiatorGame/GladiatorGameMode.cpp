// Fill out your copyright notice in the Description page of Project Settings.


#include "GladiatorGameMode.h"
#include "GladiatorHUD.h"

AGladiatorGameMode::AGladiatorGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawn(TEXT("/Game/Blueprints/Player/BP_Gladiator"));

	if (NULL != PlayerPawn.Class)
		DefaultPawnClass = PlayerPawn.Class;

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerController(TEXT("/Game/Blueprints/Player/PC_Gladiator"));

	if (NULL != PlayerController.Class)
		PlayerControllerClass = PlayerController.Class;

	static ConstructorHelpers::FClassFinder<AHUD> Hud(TEXT("/Game/Blueprints/Player/HUD_Gladiator"));

	if (NULL != Hud.Class)
		HUDClass = Hud.Class;
}
