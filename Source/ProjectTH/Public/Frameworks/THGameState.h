// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "THGameState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTH_API ATHGameState : public AGameState
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(Replicated)
	class ATHPlayerState* MostKillUser;
	UPROPERTY(Replicated)
	int32 MostKill = 0;
	void SetMostKill();

	FTimerHandle FinGameTimerHandle;
	void FinishGame();
	void MoveToMainMenu();

private:
	int32 FinKill = 1;
};
