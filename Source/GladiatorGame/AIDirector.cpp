// Fill out your copyright notice in the Description page of Project Settings.


#include "AIDirector.h"
#include "GladiatorAIController.h"
#include "Gladiator.h"

#include <BehaviorTree/BlackboardComponent.h>

#include <Kismet/GameplayStatics.h>

// Sets default values
AAIDirector::AAIDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAIDirector::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> ActorArray;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGladiatorAIController::StaticClass(), ActorArray);
	ActorArray.Reserve(ActorArray.Num());

	for (AActor* ActorPtr : ActorArray)
	{
		if (AGladiatorAIController* AiController = Cast<AGladiatorAIController>(ActorPtr))
		{
			ValidEnemies.Push(AiController);
			AiController->GetBlackboardComponent()->SetValueAsObject(TEXT("Director"), this);
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Valid enemy found"));
		}
	}

	PreviousAiTargetPosition = FVector::Zero();

	AiTarget = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	GetWorld()->GetTimerManager().SetTimer(TargetRecalculateHandle, this, &AAIDirector::CalculateTargetPositions,
										   CalculationRate, true);

	GetWorld()->GetTimerManager().SetTimer(AttackHandle, this, &AAIDirector::AttackTarget,
										   AttackRate, true);
}

void AAIDirector::CalculateTargetPositions()
{
	FVector				PlayerLocation = AiTarget->GetActorLocation();

	/*if (!CheckMinimumTargetDistance(PlayerLocation))
		return;*/

	TArray<AGladiatorAIController*>	InvalidEnemies;

	FVector2D			PlayerLocation2D = FVector2D(PlayerLocation.X, PlayerLocation.Y);

	constexpr float		OffsetOnFailure = 1.5f;


	for (AGladiatorAIController* Enemy : ValidEnemies)
	{
		if (Enemy->IsDead())
			InvalidEnemies.Add(Enemy);

		else
			CalculateSingleTargetPosition(PlayerLocation2D, Enemy, OffsetOnFailure);
	}

	PreviousAiTargetPosition = PlayerLocation;
	InvalidateEnemies(InvalidEnemies);
}

void AAIDirector::CalculateSingleTargetPosition(
	const FVector2D& PlayerLocation2D,
	AGladiatorAIController* Enemy, float Offset, const FColor& Color)
{

	float		 Distance = Enemy->GetBlackboardComponent()->GetValueAsFloat(TEXT("IdealDistance"));
	FVector2D	 Target = PlayerLocation2D - (FVector2D)(Enemy->GetPawn()->GetActorForwardVector() * Distance);

	AdjustRotation(Enemy, Target, Offset, Color);

	Enemy->SetEnemyTargetLocation(Target);
	DrawDebugPoint(GetWorld(), { Target.X, Target.Y, Enemy->GetPawn()->GetActorLocation().Z },
				   50.f, Color, false, CalculationRate);
}

void AAIDirector::AdjustRotation(AGladiatorAIController* Enemy, FVector2D& Target, float Offset, const FColor& Color)
{
	constexpr int32		MaxAttempts = static_cast<int32>(1e3f);
	int32				Iteration = 0;
	float				CurrentAngle = Offset;

	while (!CheckValidEnemyPosition(Enemy, Target) && Iteration < MaxAttempts)
	{
		CurrentAngle += Offset;
		Target = Target.GetRotated(CurrentAngle);

		DrawDebugPoint(GetWorld(), { Target.X, Target.Y, Enemy->GetPawn()->GetActorLocation().Z },
			50.f, FColor::Red, false, CalculationRate);

		++Iteration;
	}

	DrawDebugPoint(GetWorld(), { Target.X, Target.Y, Enemy->GetPawn()->GetActorLocation().Z },
		50.f, Color, false, CalculationRate);
}

void AAIDirector::ReturnAttackToken()
{
	++AttackTokenCount;
}

bool AAIDirector::CheckValidEnemyPosition(const AGladiatorAIController* Enemy, const FVector2D& Target)
{

	for (const AGladiatorAIController* OtherEnemy : ValidEnemies)
	{
		if (OtherEnemy == Enemy)
			continue;

		if (!OtherEnemy->IsTargetPositionValid(Target))
			return false;
	}

	return true;
}

bool AAIDirector::CheckMinimumTargetDistance(const FVector& CurrentPosition) const
{
	return FVector::DistSquared(PreviousAiTargetPosition, CurrentPosition) >
		   (MinimumTargetMovement * MinimumTargetMovement);
}

void AAIDirector::InvalidateEnemies(const TArray<AGladiatorAIController*>& InvalidEnemies)
{
	for (AGladiatorAIController* DeadEnemy : InvalidEnemies)
		ValidEnemies.Remove(DeadEnemy);
}

void AAIDirector::AttackTarget()
{
	int32	MaxAttempts = ValidEnemies.Num() * 10;

	if ((!ValidEnemies.Num()) || (AttackTokenCount < 1))
		return;

	AGladiatorAIController* SelectedController = ValidEnemies[FMath::RandRange(0, ValidEnemies.Num() - 1)];

	SelectedController->GetBlackboardComponent()->SetValueAsBool(TEXT("ShouldAttack"), true);

	--AttackTokenCount;
}

bool AAIDirector::IsEnemyReady(AGladiatorAIController* SelectedController)
{
	return /*SelectedController->IsCloseToTarget() &&
		   SelectedController->GetBlackboardComponent()->GetValueAsBool(TEXT("HasLineOfSight"))*/ true;
}

// Called every frame
void AAIDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


