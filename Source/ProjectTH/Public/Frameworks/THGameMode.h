// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "THGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTH_API ATHGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void SwapPlayerControllers(APlayerController* OldPC, APlayerController* NewPC);
	virtual void Logout(AController* Exiting) override;

	virtual void SpawnPlayer(APlayerController* PC, TSubclassOf<class ABaseHero> Hero);

protected:
	TArray<APlayerController*> PlayerControllersOnGame;
	virtual const FTransform FindTransformToSpawn();
};
