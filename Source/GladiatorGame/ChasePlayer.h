// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "ChasePlayer.generated.h"

/**
 *
 */
UCLASS()
class GLADIATORGAME_API UChasePlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	UChasePlayer();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


	UPROPERTY(EditAnywhere, Category = "Parameters")
	FName	SpeedKey = "ChaseSpeed";

	UPROPERTY(EditAnywhere, Category = "Parameters")
	bool	bTargetReached = false;
};
