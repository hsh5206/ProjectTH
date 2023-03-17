// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSubsystem.h"
#include "THGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTH_API UTHGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

	/** Multiplay */
	IOnlineSubsystem* OSS;
	IOnlineSessionPtr SessionInterface;
	void Host();

private:
	/** OSS's Interfaces' Callbacks */
	void OnCreateSessionComplete(FName SessionName, bool bSuccess);
};
