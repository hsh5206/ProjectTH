// Fill out your copyright notice in the Description page of Project Settings.


#include "Frameworks/THPlayerController.h"
#include "Kismet/GameplayStatics.h"

#include "Frameworks/THGameMode.h"
#include "Frameworks/THHUD.h"
#include "Frameworks/THPlayerState.h"
#include "Characters/BaseHero.h"
#include "Widgets/Widget_BaseUI.h"
#include "AbilitySystem/THAttributeSet.h"
#include "DataAssets/HeroData.h"
#include "Frameworks/GameModes/MatchGameMode_FreeForAll.h"
#include "Frameworks/GameModes/MainMenuGameMode.h"

void ATHPlayerController::BeginPlay()
{
	if (IsLocalPlayerController())
	{
		ServerSpawnPlayer();
	}

	THHUD = Cast<ATHHUD>(GetHUD());
}

void ATHPlayerController::ServerSpawnPlayer_Implementation()
{
	ATHGameMode* GameMode = Cast<ATHGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (AMatchGameMode_FreeForAll* MatchGameMode_FFA = Cast<AMatchGameMode_FreeForAll>(GameMode))
	{
		MatchGameMode_FFA->SpawnPlayer(this, SelectedHero);
	}
}

void ATHPlayerController::SpawnDefaultHUD()
{
	Super::SpawnDefaultHUD();

}

void ATHPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

}

void ATHPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	if (ABaseHero* Hero = Cast<ABaseHero>(aPawn))
	{
		if (ATHPlayerState* THPS = Cast<ATHPlayerState>(Hero->GetPlayerState()))
		{
			Hero->ServerSetHPBarPercent(THPS->GetAttributeSet()->GetHealth(), THPS->GetAttributeSet()->GetMaxHealth());
		}
	}
}