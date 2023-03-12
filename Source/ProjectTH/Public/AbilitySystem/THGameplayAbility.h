// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "THGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTH_API UTHGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UTHGameplayAbility();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled);

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TArray<TSubclassOf<UGameplayEffect>> EffetsDuringAbility;
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TArray<TSubclassOf<UGameplayEffect>> EffectsInfiniteAbility;

protected:
	TArray<FActiveGameplayEffectHandle> RemoveOnEndEffetHandles;

	UFUNCTION(blueprintCallable, BlueprintPure)
	class ABaseHero* GetHeroFromActorInfo() const;
};
