// Fill out your copyright notice in the Description page of Project Settings.


#include "Frameworks/THGameMode.h"

ATHGameMode::ATHGameMode()
{
	//bUseSeamlessTravel = true;
}

void ATHGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	PlayerControllersOnGame.Add(NewPlayer);
}

void ATHGameMode::SwapPlayerControllers(APlayerController* OldPC, APlayerController* NewPC)
{
	Super::SwapPlayerControllers(OldPC, NewPC);

	PlayerControllersOnGame.Add(NewPC);
}

void ATHGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	PlayerControllersOnGame.Remove(Cast<APlayerController>(Exiting));
}
