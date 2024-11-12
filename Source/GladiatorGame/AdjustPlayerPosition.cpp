// Fill out your copyright notice in the Description page of Project Settings.


#include "AdjustPlayerPosition.h"
#include "AIDirector.h"
#include "GladiatorAIController.h"

#include <AIController.h>
#include <BehaviorTree/BlackboardComponent.h>

UAdjustPlayerPosition::UAdjustPlayerPosition()
{
	bCreateNodeInstance = true;
	NodeName = "Adjust target position";
}

EBTNodeResult::Type UAdjustPlayerPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetAIOwner()->GetBlackboardComponent();
	FVector				  Target = Blackboard->GetValueAsVector(TEXT("TargetPosition"));
	FVector2D			  Target2D = { Target.X, Target.Y };


	AAIDirector* Director = Cast<AAIDirector>(Blackboard->GetValueAsObject(TEXT("Director")));

	Director->AdjustRotation(CastChecked<AGladiatorAIController>(OwnerComp.GetAIOwner()),
							 Target2D, Offset, FColor::Yellow);

	CastChecked<AGladiatorAIController>(OwnerComp.GetAIOwner())->SetEnemyTargetLocation(Target2D);

	return EBTNodeResult::Succeeded;
}
