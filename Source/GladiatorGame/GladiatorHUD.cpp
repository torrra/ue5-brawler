// Fill out your copyright notice in the Description page of Project Settings.


#include "GladiatorHUD.h"
#include "GladiatorLifeWidget.h"

void AGladiatorHUD::UpdateLifeRatio(float NewRatio)
{
	LifeWidget->UpdateLifeRatio(NewRatio);
}


