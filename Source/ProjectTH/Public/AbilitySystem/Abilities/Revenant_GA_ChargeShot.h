// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/THGameplayAbility.h"
#include "Revenant_GA_ChargeShot.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTH_API URevenant_GA_ChargeShot : public UTHGameplayAbility
{
	GENERATED_BODY()
	
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled);

	FTimerHandle StackTimer;
	int32 Stack = 1;
	void StackUp();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ABaseProjectile> ProjectileClass;
	UFUNCTION(BlueprintCallable)
	void Fire(const FVector& HitTarget);
};
