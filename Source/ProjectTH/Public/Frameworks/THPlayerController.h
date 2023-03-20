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
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class ABaseHero> SelectedHero;
	UFUNCTION(Server, Reliable)
	void ServerSpawnPlayer();

	virtual void PlayerTick(float DeltaTime);
	virtual void SpawnDefaultHUD() override;

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* aPawn) override;

private:
	class ATHHUD* THHUD;
};
