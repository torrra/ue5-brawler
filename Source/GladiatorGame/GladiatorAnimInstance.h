// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GladiatorAnimInstance.generated.h"

/**
 *
 */
UCLASS()
class GLADIATORGAME_API UGladiatorAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Speed;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsDead;


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsAttacking;


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool	bIsFalling;


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool	bIsJumping;

};
