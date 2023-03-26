// Fill out your copyright notice in the Description page of Project Settings.


#include "Frameworks/THHUD.h"

#include "Widgets/Widget_BaseUI.h"
#include "Characters/BaseHero.h"
#include "DataAssets/HeroData.h"
#include "Frameworks/THPlayerState.h"
#include "AbilitySystem/THAttributeSet.h"
#include "Frameworks/THPlayerController.h"

void ATHHUD::BeginPlay()
{
	Super::BeginPlay();

	// DefaultBaseUISettingWhenSpawned();
}

void ATHHUD::DefaultBaseUISettingWhenSpawned()
{
	if (ATHPlayerController* THPC = Cast<ATHPlayerController>(GetOwningPlayerController()))
	{
		if (BaseUIClass)
		{
			BaseUI = CreateWidget<UWidget_BaseUI>(THPC, BaseUIClass);
			BaseUI->AddToViewport();

			if (ABaseHero* Hero = Cast<ABaseHero>(GetOwningPawn()))
			{
				SetSkillImages();
			}

		}

		if (ABaseHero* Hero = Cast<ABaseHero>(GetOwningPawn()))
		{
			if (ATHPlayerState* THPS = Cast<ATHPlayerState>(Hero->GetPlayerState()))
			{
				if (ATHHUD* THHUD = Cast<ATHHUD>(THPC->GetHUD()))
				{
					THHUD->SetHUDMaxHealth(THPS->GetAttributeSet()->GetMaxHealth());
					THHUD->SetHUDHealth(THPS->GetAttributeSet()->GetHealth());
					THHUD->SetHUDBulletNum(THPS->GetAttributeSet()->GetBulletNum());
					THHUD->SetHUDMaxBulletNum(THPS->GetAttributeSet()->GetMaxBulletNum());
				}
			}
		}
	}
}

void ATHHUD::SetHUDHealth(float Health)
{
	if (BaseUI && BaseUI->Health)
	{
		BaseUI->SetHealthText(Health);
		BaseUI->SetHealthBarPercent(Health, BaseUI->GetMaxHealthText());

		/*if (ABaseHero* Hero = Cast<ABaseHero>(GetOwningPawn()))
		{
			Hero->ServerSetHPBarPercent(Health, BaseUI->GetMaxHealthText());
		}*/
	}
}

void ATHHUD::SetHUDMaxHealth(float MaxHealth)
{
	if (BaseUI && BaseUI->MaxHealth)
	{
		BaseUI->SetMaxHealthText(MaxHealth);
		BaseUI->SetHealthBarPercent(BaseUI->GetHealthText(), MaxHealth);

		/*if (ABaseHero* Hero = Cast<ABaseHero>(GetOwningPawn()))
		{
			Hero->ServerSetHPBarPercent(BaseUI->GetHealthText(), MaxHealth);
		}*/
	}
}

void ATHHUD::SetHUDBulletNum(float BN)
{
	if (BaseUI && BaseUI->BulletNum)
	{
		BaseUI->SetBulletNumText(BN);
	}
}

void ATHHUD::SetHUDMaxBulletNum(float MaxBN)
{
	if (BaseUI && BaseUI->MaxBulletNum)
	{
		BaseUI->SetMaxBulletNumText(MaxBN);
	}
}

void ATHHUD::SetHUDUltimateGauge(float UG)
{
	if (BaseUI && BaseUI->UltimateGaugeBar && BaseUI->UltimateGaugeText)
	{
		BaseUI->SetUltimateGaugeBarPercent(UG);
		BaseUI->SetUltimateGaugeText(UG);
	}
}

void ATHHUD::SetHUDPlayerName(const FString& Name)
{
	if (BaseUI && BaseUI->PlayerName)
	{
		BaseUI->SetPlayerNameText(Name);
	}
}

void ATHHUD::SetSkillImages()
{
	if (ABaseHero* Hero = Cast<ABaseHero>(GetOwningPawn()))
	{
		if (Hero->HeroData)
		{
			if (Hero->HeroData->HeroSkillData.ESkill) SetESkillImage(Hero->HeroData->HeroSkillData.ESkill);
			if (Hero->HeroData->HeroSkillData.ShiftSkill) SetShiftSkillImage(Hero->HeroData->HeroSkillData.ShiftSkill);
			if (Hero->HeroData->HeroSkillData.MRSkill) SetMRSkillImage(Hero->HeroData->HeroSkillData.MRSkill);
			if (Hero->HeroData->HeroSkillData.QSkill) SetQSkillImage(Hero->HeroData->HeroSkillData.QSkill);
		}
	}
}

void ATHHUD::SetESkillImage(UTexture2D* Texture)
{
	if (BaseUI)
	{
		BaseUI->SetESkillImage(Texture);
	}
}
void ATHHUD::SetShiftSkillImage(UTexture2D* Texture)
{
	if (BaseUI)
	{
		BaseUI->SetShiftSkillImage(Texture);
	}
}
void ATHHUD::SetMRSkillImage(UTexture2D* Texture)
{
	if (BaseUI)
	{
		BaseUI->SetMRSkillImage(Texture);
	}
}
void ATHHUD::SetQSkillImage(UTexture2D* Texture)
{
	if (BaseUI)
	{
		BaseUI->SetQSkillImage(Texture);
	}
}

void ATHHUD::AddWinScreen(APlayerController* PC)
{
	CreateWidget(PC, WinWidgetClass)->AddToViewport();
}

void ATHHUD::AddLoseScreen(APlayerController* PC)
{
	CreateWidget(PC, LoseWidgetClass)->AddToViewport();
}