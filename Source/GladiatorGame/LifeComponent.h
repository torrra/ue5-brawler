// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LifeComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FComponentDeathSignature);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GLADIATORGAME_API ULifeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	ULifeComponent();

	UFUNCTION(BlueprintCallable)
	bool IsDead();


	UFUNCTION()
	void TakeDamage(float Amount);

	UFUNCTION(BlueprintCallable)
	float GetLife();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	FComponentDeathSignature OnDeath;


private:

	UPROPERTY(VisibleInstanceOnly)
	float Life = -1.f;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Life")
	float MaxLife = 5.f;

};
