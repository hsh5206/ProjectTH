// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Frameworks/THGameMode.h"
#include "MatchGameMode_FreeForAll.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTH_API AMatchGameMode_FreeForAll : public ATHGameMode
{
	GENERATED_BODY()

public:
	virtual void SpawnPlayer(APlayerController* PC, TSubclassOf<class ABaseHero> Hero);
	virtual const FTransform FindTransformToSpawn();
};
