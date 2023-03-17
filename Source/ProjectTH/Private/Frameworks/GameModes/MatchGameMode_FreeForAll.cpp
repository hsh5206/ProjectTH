// Fill out your copyright notice in the Description page of Project Settings.


#include "Frameworks/GameModes/MatchGameMode_FreeForAll.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"

#include "Characters/BaseHero.h"

void AMatchGameMode_FreeForAll::SpawnPlayer(APlayerController* PC, TSubclassOf<ABaseHero> Hero)
{
	if (APawn* ControllingPawn = PC->GetPawn())
	{
		ControllingPawn->Destroy();
	}

	FTransform TransformToSpawn = FindTransformToSpawn();
	AActor* SpawnedActor = GetWorld()->SpawnActor(Hero, &TransformToSpawn);

	PC->Possess(Cast<APawn>(SpawnedActor));
}

const FTransform AMatchGameMode_FreeForAll::FindTransformToSpawn()
{
	TArray<AActor*> PlayerStarts;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);

	int32 idx = FMath::FRandRange(0, PlayerStarts.Num() - 1);
	return PlayerStarts[idx]->GetActorTransform();
}