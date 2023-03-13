// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_HealthBar.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTH_API UWidget_HealthBar : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;
	void SetHPBarPercent(float CurrentHP, float MaxHP);
};
