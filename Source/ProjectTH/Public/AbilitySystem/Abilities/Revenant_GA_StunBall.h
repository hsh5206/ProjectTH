// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/THGameplayAbility.h"
#include "Revenant_GA_StunBall.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTH_API URevenant_GA_StunBall : public UTHGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ABaseProjectile> ProjectileClass;
	UFUNCTION(BlueprintCallable)
	void Throw(const FVector& HitTarget);
};
