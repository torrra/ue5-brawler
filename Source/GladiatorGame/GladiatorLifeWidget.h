// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GladiatorLifeWidget.generated.h"

/**
 *
 */
UCLASS()
class GLADIATORGAME_API UGladiatorLifeWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void UpdateLifeRatio(float NewRatio);

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Life")
	float LifeRatio = 1.f;
};
