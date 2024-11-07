// Fill out your copyright notice in the Description page of Project Settings.


#include "AIDirector.h"
#include "GladiatorAIController.h"

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
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Orange, TEXT("Valid enemy found"));
		}
	}

	AiTarget = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	GetWorld()->GetTimerManager().SetTimer(TargetRecalculateHandle, this, &AAIDirector::CalculateTargetPositions,
										   CalculationRate, true);
}

void AAIDirector::CalculateTargetPositions()
{
	FVector				PlayerLocation = AiTarget->GetActorLocation();

	if (!CheckMinimumTargetDistance(PlayerLocation))
		return;

	TArray<AGladiatorAIController*>	InvalidEnemies;

	FVector2D			PlayerLocation2D = FVector2D(PlayerLocation.X, PlayerLocation.Y);

	constexpr float		AngleOffset = 15.f;
	constexpr float		OffsetOnFailure = AngleOffset / 10.f;
	constexpr int32		MaxAttempts = static_cast<int32>(1e3f);

	float				CurrentAngle = 0.f;//AiTarget->GetActorRotation().Yaw;

	for (AGladiatorAIController* Enemy : ValidEnemies)
	{
		if (Enemy->IsDead())
			InvalidEnemies.Add(Enemy);

		float		 Distance = Enemy->GetBlackboardComponent()->GetValueAsFloat(TEXT("IdealDistance"));
		/*FVector2D	 Target { Distance * FMath::Cos(CurrentAngle), Distance * FMath::Sin(CurrentAngle) };

		Target += PlayerLocation2D;



		CurrentAngle += AngleOffset + (FMath::FRand() * AngleOffset);*/

		FVector2D Target = PlayerLocation2D - (FVector2D)(Enemy->GetPawn()->GetActorForwardVector() * Distance);

		int32		 Iteration = 0;
		while (!CheckValidEnemyPosition(Enemy, Target) && Iteration < MaxAttempts)
		{
			CurrentAngle += OffsetOnFailure;

			//Target = PlayerLocation2D;
			Target = Target.GetRotated(CurrentAngle);

			DrawDebugPoint(GetWorld(), { Target.X, Target.Y, Enemy->GetPawn()->GetActorLocation().Z },
				50.f, FColor::Red, false, CalculationRate);
			//Target = { Distance * FMath::Cos(CurrentAngle), Distance * FMath::Sin(CurrentAngle) };
			//Target += PlayerLocation2D;
			++Iteration;
		}

		Enemy->SetEnemyTargetLocation(Target);
		DrawDebugPoint(GetWorld(), { Target.X, Target.Y, Enemy->GetPawn()->GetActorLocation().Z},
					   50.f, FColor::Magenta, false, CalculationRate);

	}

	PreviousAiTargetPosition = PlayerLocation;
	InvalidateEnemies(InvalidEnemies);
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

// Called every frame
void AAIDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


