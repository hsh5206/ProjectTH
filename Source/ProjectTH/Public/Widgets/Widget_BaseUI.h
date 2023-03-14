// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_BaseUI.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTH_API UWidget_BaseUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Health;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MaxHealth;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* BulletNum;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MaxBulletNum;

	UFUNCTION()
	float GetHealthBarPercent();
	UFUNCTION()
	float GetHealthText();
	UFUNCTION()
	float GetMaxHealthText();
	UFUNCTION()
	float GetBulletNumText();
	UFUNCTION()
	float GetMaxBulletNumText();

	UFUNCTION()
	void SetHealthBarPercent(float CurrentHP, float MaxHP);
	UFUNCTION()
	void SetHealthText(float MaxHP);
	UFUNCTION()
	void SetMaxHealthText(float MaxHP);
	UFUNCTION()
	void SetBulletNumText(float MaxHP);
	UFUNCTION()
	void SetMaxBulletNumText(float MaxHP);
};
