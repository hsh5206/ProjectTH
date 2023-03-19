// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/THAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "Components/WidgetComponent.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"

#include "Characters/BaseHero.h"

UTHAttributeSet::UTHAttributeSet()
{
}

void UTHAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UTHAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTHAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTHAttributeSet, BulletNum, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTHAttributeSet, MaxBulletNum, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTHAttributeSet, UltimateGauge, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTHAttributeSet, MaxUltimateGauge, COND_None, REPNOTIFY_Always);
}

void UTHAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		// NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	if (Attribute == GetBulletNumAttribute())
	{
		// NewValue = FMath::Clamp(NewValue, 0.f, GetMaxBulletNum());
	}
	if (Attribute == GetUltimateGaugeAttribute())
	{
		// NewValue = FMath::Clamp(NewValue, 0.f, GetMaxUltimateGauge());
	}
}

void UTHAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		//SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
	}

	if (Data.EvaluatedData.Attribute == GetBulletNumAttribute())
	{
		SetBulletNum(FMath::Clamp(GetBulletNum(), 0.0f, GetMaxBulletNum()));
	}

	if (Data.EvaluatedData.Attribute == GetUltimateGaugeAttribute())
	{
		SetUltimateGauge(FMath::Clamp(GetUltimateGauge(), 0.0f, GetMaxUltimateGauge()));
	}
}

void UTHAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTHAttributeSet, Health, OldHealth);
}

void UTHAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTHAttributeSet, MaxHealth, OldMaxHealth);
}

void UTHAttributeSet::OnRep_BulletNum(const FGameplayAttributeData& OldBulletNum)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTHAttributeSet, BulletNum, OldBulletNum);
}

void UTHAttributeSet::OnRep_MaxBulletNum(const FGameplayAttributeData& OldMaxBulletNum)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTHAttributeSet, MaxBulletNum, OldMaxBulletNum);
}

void UTHAttributeSet::OnRep_UltimateGauge(const FGameplayAttributeData& OldUltimateGauge)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTHAttributeSet, UltimateGauge, OldUltimateGauge);
}

void UTHAttributeSet::OnRep_MaxUltimateGauge(const FGameplayAttributeData& OldMaxUltimateGauge)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTHAttributeSet, MaxUltimateGauge, OldMaxUltimateGauge);
}
