// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/THGameplayAbility.h"

#include "AbilitySystem/THAbilitySystemComponent.h"
#include "Characters/BaseHero.h"

UTHGameplayAbility::UTHGameplayAbility()
{
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted; // 로컬->서버 실행
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UTHGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	FGameplayEffectContextHandle EffectContext = ActorInfo->AbilitySystemComponent->MakeEffectContext();
	for (auto GameplayEffect : EffectsInfiniteAbility)
	{
		if (!GameplayEffect.Get()) continue;

		if (UAbilitySystemComponent* AbilitySystem = ActorInfo->AbilitySystemComponent.Get())
		{
			FGameplayEffectSpecHandle SpecHandle = AbilitySystem->MakeOutgoingSpec(GameplayEffect, 1, EffectContext);
			if (SpecHandle.IsValid())
			{
				FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystem->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
			}
		}
	}

	if (IsInstantiated())
	{
		for (auto GameplayEffect : EffetsDuringAbility)
		{
			if (!GameplayEffect.Get()) continue;

			if (UAbilitySystemComponent* AbilitySystem = ActorInfo->AbilitySystemComponent.Get())
			{
				FGameplayEffectSpecHandle SpecHandle = AbilitySystem->MakeOutgoingSpec(GameplayEffect, 1, EffectContext);
				if (SpecHandle.IsValid())
				{
					FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystem->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
					if (ActiveGEHandle.WasSuccessfullyApplied())
					{
						RemoveOnEndEffetHandles.Add(ActiveGEHandle);
					}
				}
			}
		}
	}
}

void UTHGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (IsInstantiated())
	{
		/** RemoveOnEndEffetHandles Effects 해제 */
		for (FActiveGameplayEffectHandle ActiveEffectHandle : RemoveOnEndEffetHandles)
		{
			if (ActiveEffectHandle.IsValid())
			{
				ActorInfo->AbilitySystemComponent->RemoveActiveGameplayEffect(ActiveEffectHandle);
			}

		}

		RemoveOnEndEffetHandles.Empty();
	}

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

ABaseHero* UTHGameplayAbility::GetHeroFromActorInfo() const
{
	return Cast<ABaseHero>(GetAvatarActorFromActorInfo());
}
