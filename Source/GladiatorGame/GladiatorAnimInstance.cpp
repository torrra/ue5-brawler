// Fill out your copyright notice in the Description page of Project Settings.


#include "GladiatorAnimInstance.h"
#include "Gladiator.h"
#include "LifeComponent.h"

#include <GameFramework/CharacterMovementComponent.h>

void UGladiatorAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AGladiator* Gladiator = Cast<AGladiator>(TryGetPawnOwner());

	if (Gladiator)
	{
		Speed = Gladiator->GetCharacterMovement()->Velocity.Size();

		/*if (Speed > 0.f)
			__debugbreak();*/

		bIsDead = Gladiator->GetLifeComponent()->IsDead();
		bIsAttacking = Gladiator->IsAttacking();
		bIsJumping = Gladiator->bPressedJump;

		bIsFalling = Gladiator->GetCharacterMovement()->IsFalling() && !bIsJumping;
	}
}