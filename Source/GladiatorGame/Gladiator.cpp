// Fill out your copyright notice in the Description page of Project Settings.


#include "Gladiator.h"
#include "LifeComponent.h"
#include "GladiatorAnimInstance.h"

#include <Components/CapsuleComponent.h>
#include <Engine/DamageEvents.h>
#include <InputActionValue.h>
#include <GameFramework/CharacterMovementComponent.h>

// Sets default values
AGladiator::AGladiator()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Life = CreateDefaultSubobject<ULifeComponent>(TEXT("LifeComponent"));

	if (Life)
	{
		Life->OnDeath.AddDynamic(this, &AGladiator::OnDeath);
	}
}

float AGladiator::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	Life->TakeDamage(ActualDamage);

	GetMesh()->SetMaterial(0, DamageMaterial);

	if (SecondaryDamageMaterial)
		GetMesh()->SetMaterial(1, SecondaryDamageMaterial);

	GetWorld()->GetTimerManager().SetTimer(DamageMaterialHandle, this, &AGladiator::ResetMaterial, DamageMaterialTime, false);

	UpdateDamage();

	return ActualDamage;
}

void AGladiator::UpdateDamage_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, TEXT("Default damage update"));
}

ULifeComponent* AGladiator::GetLifeComponent()
{
	return Life;
}

bool AGladiator::IsAttacking()
{
	return bIsAttacking;
}

bool AGladiator::IsJumping()
{
	bool bJumping = bIsJumping;

	bIsJumping = false;
	return bJumping;
}

void AGladiator::StartDamage()
{
	AttackVolume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AGladiator::StopDamage()
{
	AttackVolume->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AGladiator::BeginPlay()
{
	Super::BeginPlay();

	AttackVolume = CastChecked<UPrimitiveComponent>(AttackVolumeReference.GetComponent(this));

	AttackVolume->OnComponentBeginOverlap.AddDynamic(this, &AGladiator::OnDealDamage);
	AttackVolume->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	InitialMaterial = GetMesh()->GetMaterial(0);
	SecondaryInitialMaterial = GetMesh()->GetMaterial(1);
}

// Called every frame
void AGladiator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGladiator::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AGladiator::OnDeath()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, TEXT("I am dead\n"));

	GetMovementComponent()->Deactivate();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
}

void AGladiator::OnDealDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	double CurrentTime = GetWorld()->GetTime().GetWorldTimeSeconds();
	double Diff = CurrentTime - LastDamageTime;


	if (Diff < DamageCooldown)
		return;


	if (OtherActor != this)
	{
		OtherActor->TakeDamage(AttackDamage, FDamageEvent(), GetController(), this);
		LastDamageTime = CurrentTime;
	}
}

void AGladiator::ResetMaterial()
{
	GetMesh()->SetMaterial(0, InitialMaterial);

	if (SecondaryInitialMaterial)
		GetMesh()->SetMaterial(1, SecondaryInitialMaterial);
}

void AGladiator::Move(const FInputActionValue& InputValue)
{
	FVector2D ValueVector = InputValue.Get<FVector2D>();
	FRotator  Rotation = FRotator(0.0, GetControlRotation().Yaw, 0.0);

	AddMovementInput(Rotation.RotateVector(FVector::ForwardVector), ValueVector.Y);
	AddMovementInput(Rotation.RotateVector(FVector::RightVector), ValueVector.X);
}

void AGladiator::Jump()
{
	Super::Jump();
}


void AGladiator::StartAttack()
{
	bIsAttacking = true;
	GetCharacterMovement()->StopMovementImmediately();
	GetCharacterMovement()->DisableMovement();
}

void AGladiator::StopAttacking()
{
	bIsAttacking = false;
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}
