// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTH_API UBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly)
	class ABaseHero* Hero;
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	class UCharacterMovementComponent* Movement;

	UPROPERTY(BlueprintReadWrite)
	float AOYaw = 0.f;
	UPROPERTY(BlueprintReadWrite)
	float AOPitch = 0.f;

	UPROPERTY(BlueprintReadWrite, Category = Movement)
	float Speed;
	UPROPERTY(BlueprintReadWrite, Category = Movement)
	float Direction;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool bIsInAir;
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool bIsMoving;
};
