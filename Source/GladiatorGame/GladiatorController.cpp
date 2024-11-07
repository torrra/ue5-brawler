// Fill out your copyright notice in the Description page of Project Settings.


#include "GladiatorController.h"
#include "Gladiator.h"

#include <InputActionValue.h>
#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>

void AGladiatorController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(MappingContext, 0);
	}

}

void AGladiatorController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);


	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGladiatorController::Look);

}

void AGladiatorController::OnPossess(APawn* ControlledPawn)
{
	Super::OnPossess(ControlledPawn);

	AGladiator*					Gladiator = CastChecked<AGladiator>(ControlledPawn);
	UEnhancedInputComponent*	EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, Gladiator, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, Gladiator, &ACharacter::StopJumping);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, Gladiator, &AGladiator::Move);

	EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, Gladiator, &AGladiator::StartAttack);
	EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Completed, Gladiator, &AGladiator::StopAttacking);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("PlayerController::OnPossess()"));

}

void AGladiatorController::Look(const FInputActionValue& InputValue)
{
	FVector2D ValueVector = InputValue.Get<FVector2D>();

	AddYawInput(ValueVector.X);
	AddPitchInput(ValueVector.Y);

}
