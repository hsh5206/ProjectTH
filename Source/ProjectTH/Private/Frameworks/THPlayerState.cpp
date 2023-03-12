// Fill out your copyright notice in the Description page of Project Settings.


#include "Frameworks/THPlayerState.h"

#include "AbilitySystem/THAbilitySystemComponent.h"
#include "AbilitySystem/THAttributeSet.h"

ATHPlayerState::ATHPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UTHAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UTHAttributeSet>(TEXT("AttributeSet"));
	NetUpdateFrequency = 100.0f;
}

UAbilitySystemComponent* ATHPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;;
}

UTHAttributeSet* ATHPlayerState::GetAttributeSet() const
{
	return AttributeSet;
}
