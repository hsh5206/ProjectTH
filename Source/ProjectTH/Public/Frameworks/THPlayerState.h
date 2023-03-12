// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "THPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTH_API ATHPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	ATHPlayerState();
	class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	class UTHAttributeSet* GetAttributeSet() const;

protected:
	UPROPERTY()
	class UTHAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	class UTHAttributeSet* AttributeSet;
};
