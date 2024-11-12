// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "AdjustPlayerPosition.generated.h"

/**
 *
 */
UCLASS()
class GLADIATORGAME_API UAdjustPlayerPosition : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	UAdjustPlayerPosition();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = "Parameters")
	float Offset;

	/*UPROPERTY(EditAnywhere, Category = "Parameters")
	float StepBackDistance;*/
};
