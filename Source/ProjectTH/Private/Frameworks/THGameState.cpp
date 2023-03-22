// Fill out your copyright notice in the Description page of Project Settings.


#include "Frameworks/THGameState.h"
#include "Blueprint/UserWidget.h"
#include "Net/UnrealNetwork.h"
#include "TimerManager.h"

#include "Frameworks/THPlayerState.h"
#include "Frameworks/THGameInstance.h"

void ATHGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATHGameState, MostKill);
	DOREPLIFETIME(ATHGameState, MostKillUser);
}

void ATHGameState::SetMostKill()
{
	int32 MostKillAmount = 0;
	for (TObjectPtr<APlayerState> PlayerState : PlayerArray)
	{
		int32 temp = Cast<ATHPlayerState>(PlayerState)->Kill;
		if (MostKillAmount < temp)
		{
			MostKillAmount = temp;
			MostKillUser = Cast<ATHPlayerState>(PlayerState);
		}
	}

	MostKill = MostKillAmount;
	

	if (MostKillAmount >= FinKill)
	{
		FinishGame();
	}
}

void ATHGameState::FinishGame()
{
	
	UE_LOG(LogTemp, Warning, TEXT("FINGAME : %d"), PlayerArray.Num());

	for (TObjectPtr<APlayerState> PlayerState : PlayerArray)
	{
		UE_LOG(LogTemp, Warning, TEXT("AddViewport"));

		ATHPlayerState* THPS = Cast<ATHPlayerState>(PlayerState);
		if (THPS)
		{
			UE_LOG(LogTemp, Warning, TEXT("AddViewport"));

			THPS->Kill = 0;
			THPS->Death = 0;

			if (THPS == MostKillUser)
			{
				THPS->AddWinScreen();
				continue;
			}
			 
			THPS->AddLoseScreen();
		}
	}

	GetWorldTimerManager().SetTimer(FinGameTimerHandle, this, &ATHGameState::MoveToMainMenu, 1.f, true);
}

void ATHGameState::MoveToMainMenu()
{
	GetWorldTimerManager().ClearTimer(FinGameTimerHandle);
	Cast<UTHGameInstance>(GetGameInstance())->DestroySession();
	GetWorld()->ServerTravel("/Game/Maps/Level_MainMenus?listen");
}