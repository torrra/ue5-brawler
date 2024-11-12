// Fill out your copyright notice in the Description page of Project Settings.


#include "LifeComponent.h"
#include "GladiatorHUD.h"

#include <GameFramework/Character.h>
#include <GameFramework/PlayerController.h>

// Sets default values for this component's properties
ULifeComponent::ULifeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

bool ULifeComponent::IsDead()
{
	return Life == 0.f;
}

void ULifeComponent::TakeDamage(float Amount)
{
	Life -= Amount;

	if (Life < 0.f || FMath::IsNearlyZero(Life))
	{
		Life = 0.f;

		OnDeath.Broadcast();
	}
	else if (GEngine)
	{
		FString Message = FString::Printf(TEXT("Still alive with %f HP\n"), Life);
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, Message);
	}

	if (Hud)
		Hud->UpdateLifeRatio(Life / MaxLife);

}


// Called when the game starts
void ULifeComponent::BeginPlay()
{
	Super::BeginPlay();

	Life = MaxLife;

	FindPlayerHud();
}

void ULifeComponent::FindPlayerHud()
{
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());

	if (!OwnerCharacter)
		return;

	APlayerController* PlayerController = Cast<APlayerController>(OwnerCharacter->GetController());

	if (!PlayerController)
		return;

	Hud = Cast<AGladiatorHUD>(PlayerController->GetHUD());

}


