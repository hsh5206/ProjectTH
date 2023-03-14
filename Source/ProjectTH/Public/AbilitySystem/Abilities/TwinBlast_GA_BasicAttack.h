// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/THGameplayAbility.h"
#include "TwinBlast_GA_BasicAttack.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTH_API UTwinBlast_GA_BasicAttack : public UTHGameplayAbility
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ABaseProjectile> ProjectileClass;
	UFUNCTION(BlueprintCallable)
	void FireL(const FVector& HitTarget);
	UFUNCTION(BlueprintCallable)
	void FireR(const FVector& HitTarget);
};
