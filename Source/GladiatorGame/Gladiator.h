// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Gladiator.generated.h"

UCLASS()
class GLADIATORGAME_API AGladiator : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGladiator();

	float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser) override;

	class ULifeComponent* GetLifeComponent();

	bool IsAttacking();
	bool IsJumping();

	void StartDamage();
	void StopDamage();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	void StartAttack(const struct FInputActionValue& InputValue);
	void StopAttacking(const struct FInputActionValue& InputValue);

	void Move(const struct FInputActionValue& InputValue);
	void Jump() override;


private:

	UFUNCTION()
	void OnDeath();


	UFUNCTION()
	void OnDealDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);


protected:

	UPROPERTY(EditAnywhere, Category = "Attack")
	FComponentReference		AttackVolumeReference;


	UPROPERTY(EditAnywhere, Category = "Attack")
	float					AttackDamage = 1.f;


private:

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class ULifeComponent> Life;

	TObjectPtr<UPrimitiveComponent>	 AttackVolume;


	UPROPERTY()
	bool	bIsAttacking = false;

	bool	bIsJumping = false;
};
