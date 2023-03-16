// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "THTypes.h"
#include "HeroData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class PROJECTTH_API UHeroData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	FAnimInfos AnimData;

	UPROPERTY(EditDefaultsOnly)
	FHeroASData HeroASData;

	UPROPERTY(EditDefaultsOnly)
	FHeroSkillData HeroSkillData;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> CrossHairClass;
};
