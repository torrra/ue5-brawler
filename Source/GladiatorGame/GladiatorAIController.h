// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GladiatorAIController.generated.h"

/**
 *
 */
UCLASS()
class GLADIATORGAME_API AGladiatorAIController : public AAIController
{
	GENERATED_BODY()

public:

	AGladiatorAIController(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	void SetEnemyTargetLocation(FVector2D Target);

	bool IsTargetPositionValid(const FVector2D& Target) const;

	bool IsCloseToTarget() const;

	bool IsDead() const;

	float GetMinDistance() const;

	UFUNCTION(BlueprintCallable)
	void BeginAttackSequence();

	UFUNCTION(BlueprintCallable)
	void EndAttackSequence();

	bool IsCurrentlyAttacking();

protected:

	void BeginPlay() override;

	void OnPossess(APawn* InPawn) override;


private:

	UFUNCTION()
	void OnDeath();

	FVector	 TargetLocation;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Behavior", meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UBehaviorTree>			BehaviorTreeAsset;


protected:

	UPROPERTY(EditAnywhere, Category = "Behavior", meta = (AllowPrivateAccess = "true"))
	float							IdealDistanceToTarget;


	UPROPERTY(EditAnywhere, Category = "Behavior", meta = (AllowPrivateAccess = "true"))
	float							AcceptableDistanceError;


	UPROPERTY(EditAnywhere, Category = "Behavior", meta = (AllowPrivateAccess = "true"))
	float							ChaseSpeed;

	UPROPERTY(EditAnywhere, Category = "Behavior", meta = (AllowPrivateAccess = "true"))
	float							OnGuardWalkSpeed;


private:

	bool							bIsDead = false;

	bool							bIsCurrentlyAttacking = false;

};
