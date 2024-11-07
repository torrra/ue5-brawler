// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIDirector.generated.h"

UCLASS()
class GLADIATORGAME_API AAIDirector : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAIDirector();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void CalculateTargetPositions();

	bool CheckValidEnemyPosition(const class AGladiatorAIController* Enemy, const FVector2D& Target);

	bool CheckMinimumTargetDistance(const FVector& CurrentPosition) const;

	void InvalidateEnemies(const TArray<class AGladiatorAIController*>& InvalidEnemies);

	TArray<class AGladiatorAIController*>	 ValidEnemies;

	FTimerHandle							 TargetRecalculateHandle;
	FVector									 PreviousAiTargetPosition;

	TObjectPtr<ACharacter>					 AiTarget;

	// How often the AI director will recalculate Enemy target positions
	UPROPERTY(EditDefaultsOnly, Category = "Enemy management", meta = (AllowPrivateAccess = "true"))
	float	CalculationRate = 0.5f;

	// Minimum change in target's position to recalculate enemy ideal positions
	UPROPERTY(EditAnywhere, Category = "Enemy management", meta = (AllowPrivateAccess = "true"))
	float	MinimumTargetMovement = 100.f;


	bool	bIsDead = false;
};
