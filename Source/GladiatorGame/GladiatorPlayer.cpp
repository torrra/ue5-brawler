// Fill out your copyright notice in the Description page of Project Settings.

#include "GladiatorPlayer.h"

#include "GladiatorPlayerController.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AGladiatorPlayer::AGladiatorPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;


	if(UCharacterMovementComponent*	MovementComponent = GetCharacterMovement())
	{
		MovementComponent->bOrientRotationToMovement = true;

		MovementComponent->MaxWalkSpeed = 500.f;
		MovementComponent->MinAnalogWalkSpeed = 0.20f;
		MovementComponent->RotationRate = FRotator(0.f, 500.f, 0.f);

		MovementComponent->BrakingDecelerationWalking = 2000.f;
		MovementComponent->BrakingDecelerationFalling = 1500.f;

		MovementComponent->JumpZVelocity = 700.f;
		MovementComponent->AirControl = 0.35f;

	}

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));

	if (SpringArm)
	{
		SpringArm->SetupAttachment(RootComponent);
		SpringArm->TargetArmLength = 200.f;
		SpringArm->bUsePawnControlRotation = true;

		FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));

		if (FollowCamera)
		{
			FollowCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
			FollowCamera->bUsePawnControlRotation = false;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Unable to create FollowCamera component for %s object\n"), *GetNameSafe(this));
		}

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to create SpringArm component for %s object\n"), *GetNameSafe(this));
	}
}

// Called when the game starts or when spawned
void AGladiatorPlayer::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AGladiatorPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGladiatorPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (AGladiatorPlayerController* GladiatorController = Cast<AGladiatorPlayerController>(GetController()))
		GladiatorController->SetupPlayerInput(PlayerInputComponent);

}

