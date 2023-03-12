#pragma once

#include "CoreMinimal.h"
#include "THTypes.generated.h"

USTRUCT(BlueprintType)
struct FAnimInfos
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditDefaultsOnly, Category = "AnimData")
	class UBlendSpace* IdleWalkRunBS = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "AnimData")
	class UAimOffsetBlendSpace* AimOffsetBS = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "AnimData")
	class UAnimSequenceBase* JumpStartAnim = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "AnimData")
	class UAnimSequenceBase* JumpLoopAnim = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "AnimData")
	class UAnimSequenceBase* JumpEndAnim = nullptr;
};

USTRUCT(BlueprintType)
struct FHeroASData
{
	GENERATED_USTRUCT_BODY();

	/** Effect */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS")
	TArray<TSubclassOf<class UGameplayEffect>> DefaultAttributeSettingEffects;
	/** Ability */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS")
	TArray<TSubclassOf<class UTHGameplayAbility>> DefaultsAbilities;
};