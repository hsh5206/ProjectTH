// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Widget_BaseUI.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

float UWidget_BaseUI::GetHealthBarPercent()
{
	return HealthBar->GetPercent();
}

float UWidget_BaseUI::GetHealthText()
{
	return FCString::Atof(*Health->GetText().ToString());
}

float UWidget_BaseUI::GetMaxHealthText()
{
	return FCString::Atof(*MaxHealth->GetText().ToString());
}

float UWidget_BaseUI::GetBulletNumText()
{
	return FCString::Atof(*BulletNum->GetText().ToString());
}

float UWidget_BaseUI::GetMaxBulletNumText()
{
	return FCString::Atof(*MaxBulletNum->GetText().ToString());
}

void UWidget_BaseUI::SetHealthBarPercent(float CurrentHP, float MaxHP)
{
	HealthBar->SetPercent(CurrentHP / MaxHP);
}

void UWidget_BaseUI::SetHealthText(float HP)
{
	Health->SetText(FText::FromString(FString::Printf(TEXT("%d"), int32(HP))));
}

void UWidget_BaseUI::SetMaxHealthText(float MaxHP)
{
	MaxHealth->SetText(FText::FromString(FString::Printf(TEXT("%d"), int32(MaxHP))));
}

void UWidget_BaseUI::SetBulletNumText(float BN)
{
	BulletNum->SetText(FText::FromString(FString::Printf(TEXT("%d"), int32(BN))));
}

void UWidget_BaseUI::SetMaxBulletNumText(float MBN)
{
	MaxBulletNum->SetText(FText::FromString(FString::Printf(TEXT("%d"), int32(MBN))));
}
