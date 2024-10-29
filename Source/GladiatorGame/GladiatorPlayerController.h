// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GladiatorPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

/**
 *
 */
UCLASS()
class GLADIATORGAME_API AGladiatorPlayerController final : public APlayerController
{
	GENERATED_BODY()

public:

	void SetupPlayerInput(UInputComponent* PlayerInputComponent);

private:

	void BeginPlay() override;

	void Look(const FInputActionValue& InputValue);

	void Move(const FInputActionValue& InputValue);

	void Jump(const FInputActionValue& InputValue);
	void StopJumping(const FInputActionValue& InputValue);

	void Attack(const FInputActionValue& InputValue);

	UFUNCTION()
	void StopAttacking();

	FTimerDelegate	AttackTimerDelegate;
	FTimerHandle	AttackTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AttackAction;

	UPROPERTY()
	ACharacter*   ControlledCharacter;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	float		  AttackStateTimer;

	UPROPERTY(BluePrintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool		  bIsAttacking;

};
