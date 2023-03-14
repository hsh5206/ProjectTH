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

protected:
	virtual void BeginPlay() override;
	
};
