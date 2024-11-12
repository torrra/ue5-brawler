// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "CheckLineOfSightService.generated.h"

/**
 *
 */
UCLASS()
class GLADIATORGAME_API UCheckLineOfSightService : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:

	UCheckLineOfSightService();

	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;


};
