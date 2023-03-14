// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
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
};
