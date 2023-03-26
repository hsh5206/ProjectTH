// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
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
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintReadOnly, Replicated)
	int32 Kill = 0;
	UPROPERTY(BlueprintReadOnly, Replicated)
	int32 Death = 0;
	UPROPERTY(BlueprintReadOnly, Replicated)
	FString Name;

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	class UTHAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	class UTHAttributeSet* AttributeSet;

public:
	virtual void OnMaxHealthChanged(const FOnAttributeChangeData& Data);
	virtual void OnHealthChanged(const FOnAttributeChangeData& Data);
	virtual void OnMaxBulletNumChanged(const FOnAttributeChangeData& Data);
	virtual void OnBulletNumChanged(const FOnAttributeChangeData& Data);
	virtual void OnUltimateGaugeChanged(const FOnAttributeChangeData& Data);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastAddWinScreen();
	UFUNCTION(NetMulticast, Reliable)
	void MulticastAddLoseScreen();

private:
	class ATHPlayerController* OwningTHController;
	class ATHHUD* OwningTHHUD;
	FTimerHandle UpdateTimer;
	void DefaultSetup();
};
