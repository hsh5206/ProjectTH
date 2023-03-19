// Fill out your copyright notice in the Description page of Project Settings.


#include "Frameworks/THPlayerState.h"
#include "Net/UnrealNetwork.h"

#include "AbilitySystem/THAbilitySystemComponent.h"
#include "AbilitySystem/THAttributeSet.h"
#include "GameplayEffectExtension.h"

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

void ATHPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATHPlayerState, Kill);
	DOREPLIFETIME(ATHPlayerState, Death);
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
	GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(GetAttributeSet()->GetUltimateGaugeAttribute()).AddUObject(this, &ATHPlayerState::OnUltimateGaugeChanged);
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

	if (FMath::IsNearlyEqual(Data.NewValue, 0.f))
	{
		Cast<ABaseHero>(GetPawn())->Death();

		// AActor* FromActor = Data.GEModData->EffectSpec.GetContext().GetInstigator();
		if (Data.GEModData)
		{
			UE_LOG(LogTemp, Warning, TEXT("Data.GEModData"));
			AActor* FromActor = Data.GEModData->EffectSpec.GetEffectContext().GetInstigator();
			if (ABaseHero* FromHero = Cast<ABaseHero>(FromActor))
			{
				Cast<ATHPlayerState>(FromHero->GetPlayerState())->Kill += 1;
				Death += 1;
			}
		}
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

void ATHPlayerState::OnUltimateGaugeChanged(const FOnAttributeChangeData& Data)
{
	if (OwningTHHUD)
	{
		OwningTHHUD->SetHUDUltimateGauge(Data.NewValue);
	}
}
