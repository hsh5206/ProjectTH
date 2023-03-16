// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/THGameplayAbility.h"
#include "TwinBlaster_GA_UltimateAttack.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTH_API UTwinBlaster_GA_UltimateAttack : public UTHGameplayAbility
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ABaseProjectile> ProjectileClass;
	UFUNCTION(BlueprintCallable)
	void Fire(const FVector& HitTarget);
};
