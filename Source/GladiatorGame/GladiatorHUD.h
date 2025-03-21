// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GladiatorHUD.generated.h"

/**
 *
 */
UCLASS()
class GLADIATORGAME_API AGladiatorHUD : public AHUD
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void UpdateLifeRatio(float NewRatio);

	UFUNCTION(BlueprintImplementableEvent)
	void AllEnemiesKilled();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<class UGladiatorLifeWidget> LifeWidget;
};
