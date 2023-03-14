// Fill out your copyright notice in the Description page of Project Settings.


#include "Frameworks/THPlayerState.h"

#include "AbilitySystem/THAbilitySystemComponent.h"
#include "AbilitySystem/THAttributeSet.h"

#include "Characters/BaseHero.h"
#include "Frameworks/THPlayerController.h"
#include "Frameworks/THHUD.h"

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

void ATHPlayerState::BeginPlay()
{
	Super::BeginPlay();

	OwningTHController = Cast<ATHPlayerController>(GetOwningController());
	if (OwningTHController)
	{
		OwningTHHUD = Cast<ATHHUD>(OwningTHController->GetHUD());
	}

	GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(GetAttributeSet()->GetMaxHealthAttribute()).AddUObject(this, &ATHPlayerState::OnMaxHealthChanged);
	GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(GetAttributeSet()->GetHealthAttribute()).AddUObject(this, &ATHPlayerState::OnHealthChanged);
	GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(GetAttributeSet()->GetMaxBulletNumAttribute()).AddUObject(this, &ATHPlayerState::OnMaxBulletNumChanged);
	GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(GetAttributeSet()->GetBulletNumAttribute()).AddUObject(this, &ATHPlayerState::OnBulletNumChanged);
}

void ATHPlayerState::OnMaxHealthChanged(const FOnAttributeChangeData& Data)
{
	if (OwningTHHUD)
	{
		OwningTHHUD->SetHUDMaxHealth(Data.NewValue);
	}
}

void ATHPlayerState::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	if (OwningTHHUD)
	{
		OwningTHHUD->SetHUDHealth(Data.NewValue);
	}
}

void ATHPlayerState::OnMaxBulletNumChanged(const FOnAttributeChangeData& Data)
{
	if (OwningTHHUD)
	{
		OwningTHHUD->SetHUDMaxBulletNum(Data.NewValue);
	}
}

void ATHPlayerState::OnBulletNumChanged(const FOnAttributeChangeData& Data)
{
	if (OwningTHHUD)
	{
		OwningTHHUD->SetHUDBulletNum(Data.NewValue);
	}
}
