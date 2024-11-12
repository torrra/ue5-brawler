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


	void CalculateSingleTargetPosition(const FVector2D& PlayerLocation2D,
									   class AGladiatorAIController* Enemy,
									   float Offset,
								       const FColor& Color = FColor::Magenta);


	void AdjustRotation(class AGladiatorAIController* Enemy,
						FVector2D& Target, float Offset,
						const FColor& Color = FColor::Magenta);

	UFUNCTION(BlueprintCallable)
	void ReturnAttackToken();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void CalculateTargetPositions();

	bool CheckValidEnemyPosition(const class AGladiatorAIController* Enemy, const FVector2D& Target);

	bool CheckMinimumTargetDistance(const FVector& CurrentPosition) const;

	void InvalidateEnemies(const TArray<class AGladiatorAIController*>& InvalidEnemies);

	UFUNCTION()
	void AttackTarget();

	bool IsEnemyReady(class AGladiatorAIController* SelectedController);

	TArray<class AGladiatorAIController*>	 ValidEnemies;

	FTimerHandle							 TargetRecalculateHandle;
	FTimerHandle							 AttackHandle;
	FVector									 PreviousAiTargetPosition;

	TObjectPtr<ACharacter>					 AiTarget;

	// How often the AI director will recalculate Enemy target positions
	UPROPERTY(EditAnywhere, Category = "Enemy management", meta = (AllowPrivateAccess = "true"))
	float	CalculationRate = 0.5f;


	UPROPERTY(EditAnywhere, Category = "Enemy management", meta = (AllowPrivateAccess = "true"))
	float	AttackRate = 1.f;

	// Minimum change in target's position to recalculate enemy ideal positions
	UPROPERTY(EditAnywhere, Category = "Enemy management", meta = (AllowPrivateAccess = "true"))
	float	MinimumTargetMovement = 100.f;


	UPROPERTY(EditAnywhere, Category = "Enemy management", meta = (AllowPrivateAccess = "true"))
	int16	AttackTokenCount = 1;
	bool	bIsDead = false;
};
