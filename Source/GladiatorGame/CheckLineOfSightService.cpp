// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckLineOfSightService.h"
#include "GladiatorAIController.h"

#include <AIController.h>
#include <BehaviorTree/BlackboardComponent.h>
#include <Components/CapsuleComponent.h>
#include <GameFramework/Character.h>
#include <Kismet/KismetSystemLibrary.h>


UCheckLineOfSightService::UCheckLineOfSightService()
{
	bCreateNodeInstance = true;
	NodeName = "Check line of sight";
}

void UCheckLineOfSightService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController*			Controller = OwnerComp.GetAIOwner();
	UBlackboardComponent*	Blackboard = Controller->GetBlackboardComponent();

	AActor*					AiTarget = CastChecked<AActor>(Blackboard->GetValueAsObject(TEXT("TargetActor")));
	float					Radius = Controller->GetCharacter()->GetCapsuleComponent()->GetScaledCapsuleRadius();

	TArray<TEnumAsByte<EObjectTypeQuery>>	ObjectTypes =
	{
		UEngineTypes::ConvertToObjectType(ECC_Pawn)
	};

	TArray<AActor*> ToIgnore = { Controller->GetCharacter() };
	FHitResult		HitResult;


	// Check if enemy has a clear view of its target (player) and enough space to reach it
	bool  bHasHit =
	UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), Controller->GetCharacter()->GetActorLocation(),
													 AiTarget->GetActorLocation(),
													 Radius, ObjectTypes, false, ToIgnore, EDrawDebugTrace::ForDuration,
													 HitResult, true, FLinearColor::Green, FLinearColor::Red, 0.5f);


	float MinDistance = 10.f;

	if (AGladiatorAIController* GladiatorController = Cast<AGladiatorAIController>(Controller))
	{
		MinDistance = GladiatorController->GetMinDistance();
	}

	bool bHasLineOfSight;

	if (bHasHit)
	{
		bool bCloseEnough = FVector::Dist2D(AiTarget->GetActorLocation(), HitResult.GetActor()->GetActorLocation()) < MinDistance;

		// No hit or player hit first = clear
		bHasLineOfSight = (HitResult.GetActor() == AiTarget) || bCloseEnough;
	}
	else
		bHasLineOfSight = false;


	Blackboard->SetValueAsBool(TEXT("HasLineOfSight"), bHasLineOfSight);
}
