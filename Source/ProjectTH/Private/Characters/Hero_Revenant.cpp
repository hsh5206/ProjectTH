// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Hero_Revenant.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerState.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

AHero_Revenant::AHero_Revenant()
{
}

void AHero_Revenant::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (ShiftInputAction)
		{
			PlayerEnhancedInputComponent->BindAction(ShiftInputAction, ETriggerEvent::Started, this, &AHero_Revenant::OnShiftKey);
		}
		if (EInputAction)
		{
			PlayerEnhancedInputComponent->BindAction(EInputAction, ETriggerEvent::Started, this, &AHero_Revenant::OnEKey);
		}
		if (MRInputAction)
		{
			PlayerEnhancedInputComponent->BindAction(MRInputAction, ETriggerEvent::Started, this, &AHero_Revenant::OnMRKey);
		}
		if (QInputAction)
		{
			PlayerEnhancedInputComponent->BindAction(QInputAction, ETriggerEvent::Started, this, &AHero_Revenant::OnQKey);
		}
	}
}

void AHero_Revenant::OnShiftKey()
{
	if (IsLocallyControlled())
	{
		FGameplayEventData Payload;
		Payload.Instigator = this;
		Payload.EventTag = FGameplayTag::RequestGameplayTag(FName("Event.Ability.Shift"));
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetPlayerState(), Payload.EventTag, Payload);
	}
}

void AHero_Revenant::OnEKey()
{
	if (IsLocallyControlled())
	{
		TraceToCrossHair();

		FGameplayEventData Payload;
		Payload.Instigator = this;
		Payload.EventTag = FGameplayTag::RequestGameplayTag(FName("Event.Ability.EKey"));
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetPlayerState(), Payload.EventTag, Payload);
	}
}

void AHero_Revenant::OnMRKey()
{
	if (!bCanMR) return;

	if (IsLocallyControlled())
	{
		FGameplayEventData Payload;
		Payload.Instigator = this;
		Payload.EventTag = FGameplayTag::RequestGameplayTag(FName("Event.Ability.MRKey"));
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetPlayerState(), Payload.EventTag, Payload);
	}
}

void AHero_Revenant::OnQKey()
{
	if (IsLocallyControlled())
	{
		FGameplayEventData Payload;
		Payload.Instigator = this;
		Payload.EventTag = FGameplayTag::RequestGameplayTag(FName("Event.Ability.QKey"));
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetPlayerState(), Payload.EventTag, Payload);
	}
}
