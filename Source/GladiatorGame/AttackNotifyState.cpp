// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackNotifyState.h"
#include "Gladiator.h"

void UAttackNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	AGladiator* Gladiator = Cast<AGladiator>(MeshComp->GetOwner());

	if (Gladiator)
	{
		Gladiator->StartDamage();
	}
}

void UAttackNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	AGladiator* Gladiator = Cast<AGladiator>(MeshComp->GetOwner());

	if (Gladiator)
	{
		Gladiator->StopDamage();
	}
}
