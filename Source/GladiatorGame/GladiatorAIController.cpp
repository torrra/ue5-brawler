// Fill out your copyright notice in the Description page of Project Settings.

#include "GladiatorAIController.h"

#include "AIDirector.h"
#include "Gladiator.h"
#include "LifeComponent.h"

#include <BehaviorTree/BehaviorTreeComponent.h>
#include <BehaviorTree/BehaviorTree.h>
#include <BehaviorTree/BlackboardComponent.h>
#include <Components/CapsuleComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Navigation/CrowdFollowingComponent.h>


AGladiatorAIController::AGladiatorAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
}

void AGladiatorAIController::SetEnemyTargetLocation(FVector2D Target)
{
	TargetLocation.X = Target.X;
	TargetLocation.Z = GetPawn()->GetActorLocation().Z;
	TargetLocation.Y = Target.Y;

	if (!IsCloseToTarget())
	{
		Blackboard->SetValueAsVector(TEXT("TargetPosition"), TargetLocation);
		GetBlackboardComponent()->SetValueAsBool(TEXT("TargetReached"), false);
	}
}

void AGladiatorAIController::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*>		GladiatorArray;
	AActor*				Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	Blackboard->SetValueAsObject(TEXT("TargetActor"), Player);

	if (AGladiator* Gladiator = Cast<AGladiator>(GetCharacter()))
		Gladiator->GetLifeComponent()->OnDeath.AddDynamic(this, &AGladiatorAIController::OnDeath);

	SetFocus(Player);
}

void AGladiatorAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	RunBehaviorTree(BehaviorTreeAsset);

	// Populate blackboard
	Blackboard->SetValueAsFloat(TEXT("IdealDistance"), IdealDistanceToTarget);
	Blackboard->SetValueAsFloat(TEXT("ChaseSpeed"), ChaseSpeed);
	Blackboard->SetValueAsFloat(TEXT("OnGuardWalkSpeed"), OnGuardWalkSpeed);
}

void AGladiatorAIController::OnDeath()
{
	if (AAIDirector* Director = Cast<AAIDirector>(Blackboard->GetValueAsObject(TEXT("Director"))))
		Director->NotifyEnemyDeath(this);

	if (UBehaviorTreeComponent* BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent))
		BehaviorTreeComponent->StopLogic(TEXT("Enemy is dead"));

	bIsDead = true;
}

bool AGladiatorAIController::IsTargetPositionValid(const FVector2D& Target) const
{
	FVector2D	Location2D{ TargetLocation.X, TargetLocation.Y };
	float		RadiusSquared = GetCharacter()->GetCapsuleComponent()->GetScaledCapsuleRadius() * 2.f;

	RadiusSquared *= RadiusSquared;
	return (Location2D - Target).SizeSquared() > RadiusSquared;
}

bool AGladiatorAIController::IsCloseToTarget() const
{
	return FVector::Distance(GetCharacter()->GetActorLocation(), TargetLocation) < AcceptableDistanceError;
}

bool AGladiatorAIController::IsDead() const
{
	return bIsDead;
}

float AGladiatorAIController::GetMinDistance() const
{
	return AcceptableDistanceError;
}

void AGladiatorAIController::BeginAttackSequence()
{
	bIsCurrentlyAttacking = true;
}

void AGladiatorAIController::EndAttackSequence()
{
	bIsCurrentlyAttacking = false;
}

bool AGladiatorAIController::IsCurrentlyAttacking()
{
	return bIsCurrentlyAttacking;
}
