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
	float GetUltimateGauge();

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

	/** Skill */
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* UltimateGaugeText;
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* UltimateGaugeBar;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UImage* ShiftSkillImage;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UImage* ESkillImage;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UImage* RMSkillImage;

	UFUNCTION()
	void SetUltimateGaugeBarPercent(float CrrentGauge);
	UFUNCTION()
	void SetUltimateGaugeText(float GaugePercent);
	UFUNCTION()
	void SetESkillImage(UTexture2D* Image);
	UFUNCTION()
	void SetMRSkillImage(UTexture2D* Image);
	UFUNCTION()
	void SetShiftSkillImage(UTexture2D* Image);
	UFUNCTION()
	void SetQSkillImage(UTexture2D* Image);

};
