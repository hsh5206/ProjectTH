// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "THHUD.generated.h"

UCLASS()
class PROJECTTH_API ATHHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UWidget_BaseUI> BaseUIClass;
	UWidget_BaseUI* BaseUI;

	UFUNCTION()
	void DefaultBaseUISettingWhenSpawned();

	void SetHUDHealth(float Health);
	void SetHUDMaxHealth(float MaxHealth);
	void SetHUDBulletNum(float BN);
	void SetHUDMaxBulletNum(float MaxBN);
	void SetHUDUltimateGauge(float UG);
	
	void SetSkillImages();
	void SetESkillImage(UTexture2D* Texture);
	void SetShiftSkillImage(UTexture2D* Texture);
	void SetMRSkillImage(UTexture2D* Texture);
	void SetQSkillImage(UTexture2D* Texture);

protected:
	virtual void BeginPlay() override;
	
};
