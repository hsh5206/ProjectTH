// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Widget_BaseUI.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"

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

float UWidget_BaseUI::GetUltimateGauge()
{
	return FCString::Atof(*UltimateGaugeText->GetText().ToString());
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

void UWidget_BaseUI::SetUltimateGaugeBarPercent(float CrrentGauge)
{
	UltimateGaugeBar->SetPercent(CrrentGauge / 100.f);
}

void UWidget_BaseUI::SetUltimateGaugeText(float GaugePercent)
{
	UltimateGaugeText->SetText(FText::FromString(FString::Printf(TEXT("%d"), int32(GaugePercent))));
}

void UWidget_BaseUI::SetPlayerNameText(const FString& Name)
{
	PlayerName->SetText(FText::FromString(Name));
}

void UWidget_BaseUI::SetESkillImage(UTexture2D* Image)
{
	ESkillImage->SetBrushFromTexture(Image);
}

void UWidget_BaseUI::SetMRSkillImage(UTexture2D* Image)
{
	RMSkillImage->SetBrushFromTexture(Image);
}

void UWidget_BaseUI::SetShiftSkillImage(UTexture2D* Image)
{
	ShiftSkillImage->SetBrushFromTexture(Image);
}

void UWidget_BaseUI::SetQSkillImage(UTexture2D* Image)
{
	FSlateBrush Brush;
	Brush.SetResourceObject(Image);
	UltimateGaugeBar->WidgetStyle.SetFillImage(Brush);
}