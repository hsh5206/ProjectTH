// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/THAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "Components/WidgetComponent.h"

#include "Characters/BaseHero.h"
#include "Widgets/Widget_HealthBar.h"
#include "Frameworks/THPlayerState.h"

UTHAttributeSet::UTHAttributeSet()
{
}

void UTHAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME_CONDITION_NOTIFY(UTHAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTHAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
}

void UTHAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
}

void UTHAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	if (Attribute == GetHealthAttribute())
	{
		/** HealthBar Change */
		if (ABaseHero* Hero = Cast<ABaseHero>(Cast<ATHPlayerState>(GetOwningActor())->GetPawn()))
		{
			/*if (UMainScreenWidget* MainWidget = Hero->MainWidget)
			{
				Hero->MainWidget->SetHPBarPercent(GetHealth(), GetMaxHealth());
			}*/

			UE_LOG(LogTemp, Warning, TEXT("SetHealthBar : %f / %f = %f"), GetHealth(), GetMaxHealth(), GetHealth() / GetMaxHealth());
			Hero->ServerSetHPBarPercent(GetHealth(), GetMaxHealth());
		}
	}

	Super::PostAttributeChange(Attribute, OldValue, NewValue);
}

void UTHAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTHAttributeSet, Health, OldHealth);
}

void UTHAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTHAttributeSet, MaxHealth, OldMaxHealth);
}
