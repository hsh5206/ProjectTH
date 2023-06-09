// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseHero.h"
#include "Hero_TwinBlast.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTH_API AHero_TwinBlast : public ABaseHero
{
	GENERATED_BODY()
	
public:
	AHero_TwinBlast();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* ShiftInputAction;
	UPROPERTY(EditDefaultsOnly)
	UInputAction* EInputAction;
	UPROPERTY(EditDefaultsOnly)
	UInputAction* MRInputAction;
	UPROPERTY(EditDefaultsOnly)
	UInputAction* QInputAction;

	/** Shift Key */
	void OnShiftKey();
	/** E Key */
	void OnEKey();
	/** MR Key */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bCanMR = true;
	void OnMRKey();
	/** Q Key */
	void OnQKey();
};
