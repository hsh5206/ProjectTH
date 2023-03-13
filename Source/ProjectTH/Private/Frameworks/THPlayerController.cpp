// Fill out your copyright notice in the Description page of Project Settings.


#include "Frameworks/THPlayerController.h"
#include "Kismet/GameplayStatics.h"

#include "Frameworks/THGameMode.h"

void ATHPlayerController::BeginPlay()
{
	if (IsLocalPlayerController())
	{
		ServerSpawnPlayer();
	}
}

void ATHPlayerController::ServerSpawnPlayer_Implementation()
{
	ATHGameMode* GameMode = Cast<ATHGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->SpawnPlayer(this, SelectedHero);
}
