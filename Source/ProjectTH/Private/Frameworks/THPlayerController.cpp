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
#include "Widgets/Widget_BaseUI.h"
#include "TimerManager.h"

void ATHPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalPlayerController())
	{
		if (HeroSelectionWidgetClass)
		{
			HeroSelectWidget = CreateWidget(GetWorld(), HeroSelectionWidgetClass);
			HeroSelectWidget->AddToViewport();
		}
		Death();
	}

	THHUD = Cast<ATHHUD>(GetHUD());
}

void ATHPlayerController::Death()
{
	if (HeroSelectWidget)
	{
		HeroSelectWidget->SetVisibility(ESlateVisibility::Visible);
		SetInputMode(FInputModeUIOnly());
		SetShowMouseCursor(true);
	}
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &ATHPlayerController::ReadyToSpawnPlayer, 3.f, false);
}

void ATHPlayerController::ReadyToSpawnPlayer()
{
	GetWorldTimerManager().ClearTimer(SpawnTimer);

	if (HeroSelectWidget)
	{
		HeroSelectWidget->SetVisibility(ESlateVisibility::Hidden);
		SetInputMode(FInputModeGameOnly());
		SetShowMouseCursor(false);
	}

	ServerSpawnPlayer();
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

	/*if (ABaseHero* Hero = Cast<ABaseHero>(aPawn))
	{
		if (ATHPlayerState* THPS = Cast<ATHPlayerState>(Hero->GetPlayerState()))
		{
			Hero->ServerSetHPBarPercent(THPS->GetAttributeSet()->GetHealth(), THPS->GetAttributeSet()->GetMaxHealth());
		}
	}*/
}