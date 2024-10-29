// Fill out your copyright notice in the Description page of Project Settings.

#include "GladiatorPlayerController.h"
#include "GladiatorPlayer.h"

// Engine headers
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


void AGladiatorPlayerController::SetupPlayerInput(UInputComponent* PlayerInputComponent)
{
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem =
	ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (InputSubsystem)
		InputSubsystem->AddMappingContext(InputMappingContext, 0);

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInput)
	{
		EnhancedInput->BindAction(JumpAction, ETriggerEvent::Started, this, &AGladiatorPlayerController::Jump);
		EnhancedInput->BindAction(JumpAction, ETriggerEvent::Completed, this, &AGladiatorPlayerController::StopJumping);

		EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGladiatorPlayerController::Look);
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGladiatorPlayerController::Move);

		EnhancedInput->BindAction(AttackAction, ETriggerEvent::Started, this, &AGladiatorPlayerController::Attack);
	}
}

void AGladiatorPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ControlledCharacter = Cast<ACharacter>(GetPawn());

	if (!ControlledCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("%s is not a Character"), *(GetPawn()->GetName()));
	}

	AttackTimerDelegate.BindUFunction(this, FName("StopAttacking"));
}

void AGladiatorPlayerController::Look(const FInputActionValue& InputValue)
{
	FVector2D	ValueVector = InputValue.Get<FVector2D>();

	AddYawInput(ValueVector.X);
	AddPitchInput(ValueVector.Y);
}

void AGladiatorPlayerController::Move(const FInputActionValue& InputValue)
{
	if (bIsAttacking)
		return;

	FVector2D			ValueVector = InputValue.Get<FVector2D>();
	FRotator			YawRotation{ 0.f, GetControlRotation().Yaw, 0.f };
	FRotationMatrix		Matrix = FRotationMatrix(YawRotation);

	APawn*				ControlledPawn = GetPawn();

	ControlledPawn->AddMovementInput(Matrix.GetUnitAxis(EAxis::Y), ValueVector.X);
	ControlledPawn->AddMovementInput(Matrix.GetUnitAxis(EAxis::X), ValueVector.Y);

	//ControlledCharacter->State

	/*GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Cyan,
	FString::Printf(TEXT("Movement vector: x = %f    y = %f\n"), ValueVector.X, ValueVector.Y));*/

	//ControlledCharacter->GetCharacterMovement()->IsWalking
}

void AGladiatorPlayerController::Jump(const FInputActionValue& InputValue)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Cyan, TEXT("Jump\n"));

	if (!bIsAttacking)
		ControlledCharacter->Jump();
}

void AGladiatorPlayerController::StopJumping(const FInputActionValue& InputValue)
{
	if (!bIsAttacking)
		ControlledCharacter->StopJumping();
}

void AGladiatorPlayerController::Attack(const FInputActionValue& InputValue)
{
	if (bIsAttacking)
		return;

	bIsAttacking = true;
	GetWorldTimerManager().SetTimer(AttackTimerHandle, AttackTimerDelegate, AttackStateTimer, true);
}

void AGladiatorPlayerController::StopAttacking()
{
	bIsAttacking = false;
}
