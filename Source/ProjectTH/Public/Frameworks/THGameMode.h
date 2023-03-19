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
	ATHGameMode();
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void SwapPlayerControllers(APlayerController* OldPC, APlayerController* NewPC);
	virtual void Logout(AController* Exiting) override;

	UFUNCTION(BlueprintCallable)
	TArray<APlayerController*> GetPlayercontrollersOnGame() { return PlayerControllersOnGame; }

protected:
	TArray<APlayerController*> PlayerControllersOnGame;
};
