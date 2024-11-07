// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GladiatorController.generated.h"

/**
 *
 */
UCLASS()
class GLADIATORGAME_API AGladiatorController : public APlayerController
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay();

	virtual void SetupInputComponent() override;

	virtual void OnPossess(APawn* ControlledPawn) override;

	virtual void Look(const struct FInputActionValue& InputValue);


	UPROPERTY(EditDefaultsOnly, Category = Input)
	TObjectPtr<class UInputMappingContext>  MappingContext;


	UPROPERTY(EditDefaultsOnly, Category = Input)
	TObjectPtr<class UInputAction>		LookAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	TObjectPtr<class UInputAction>		MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	TObjectPtr<class UInputAction>		JumpAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	TObjectPtr<class UInputAction>		AttackAction;

};
