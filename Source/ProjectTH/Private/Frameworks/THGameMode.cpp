// Fill out your copyright notice in the Description page of Project Settings.


#include "Frameworks/THGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"

#include "Characters/BaseHero.h"

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

const FTransform ATHGameMode::FindTransformToSpawn()
{
	TArray<AActor*> PlayerStarts;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);

	int32 idx = FMath::FRandRange(0, PlayerStarts.Num() - 1);
	return PlayerStarts[idx]->GetActorTransform();
}

void ATHGameMode::SpawnPlayer(APlayerController* PC, TSubclassOf<ABaseHero> Hero)
{
	if (APawn* ControllingPawn = PC->GetPawn())
	{
		ControllingPawn->Destroy();
	}

	FTransform TransformToSpawn = FindTransformToSpawn();
	AActor* SpawnedActor = GetWorld()->SpawnActor(Hero, &TransformToSpawn);

	PC->Possess(Cast<APawn>(SpawnedActor));
}
