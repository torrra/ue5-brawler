// Fill out your copyright notice in the Description page of Project Settings.


#include "ChasePlayer.h"

#include <AIController.h>
#include <BehaviorTree/BlackboardComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <GameFramework/Character.h>

UChasePlayer::UChasePlayer()
{
	bCreateNodeInstance = true;
	NodeName = "Chase Player";
}


EBTNodeResult::Type UChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	UBlackboardComponent*	Blackboard = OwnerComp.GetAIOwner()->GetBlackboardComponent();

	OwnerComp.GetAIOwner()->GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = Blackboard->GetValueAsFloat(SpeedKey);
	Blackboard->SetValueAsBool(TEXT("TargetReached"), bTargetReached);
	return EBTNodeResult::Type::Succeeded;
}
