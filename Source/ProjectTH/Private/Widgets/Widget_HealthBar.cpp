// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Widget_HealthBar.h"
#include "Components/ProgressBar.h"


void UWidget_HealthBar::SetHPBarPercent(float CurrentHP, float MaxHP)
{
	if(HealthBar) HealthBar->SetPercent(CurrentHP / MaxHP);
}