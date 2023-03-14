// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/THAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "Components/WidgetComponent.h"

#include "Characters/BaseHero.h"

UTHAttributeSet::UTHAttributeSet()
{
}

void UTHAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME_CONDITION_NOTIFY(UTHAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTHAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTHAttributeSet, BulletNum, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTHAttributeSet, MaxBulletNum, COND_None, REPNOTIFY_Always);
}

void UTHAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	if (Attribute == GetBulletNumAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxBulletNum());
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
