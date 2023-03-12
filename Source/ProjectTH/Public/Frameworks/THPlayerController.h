// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "THPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTH_API ATHPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ABaseHero> SelectedHero;
};
