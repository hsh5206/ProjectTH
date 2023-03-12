// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/DataAsset.h"

#include "Characters/BaseHero.h"
#include "DataAssets/HeroData.h"

void UBaseAnimInstance::NativeInitializeAnimation()
{
	Hero = Cast<ABaseHero>(TryGetPawnOwner());
	if (Hero)
	{
		Movement = Hero->GetCharacterMovement();
	}
}

void UBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (Hero)
	{
		Speed = Hero->GetVelocity().Length();
		Direction = CalculateDirection(Hero->GetVelocity(), Hero->GetActorRotation());

		FRotator AORotator = UKismetMathLibrary::NormalizedDeltaRotator(Hero->GetBaseAimRotation(), Hero->GetActorRotation());
		AOPitch = AORotator.Pitch;
		AOYaw = AORotator.Yaw;
	}

	if (Movement)
	{
		bIsInAir = Movement->IsFalling();
	}
}

UBlendSpace* UBaseAnimInstance::GetIdleWalkRunBS() const
{
	if (Hero && Hero->HeroData)
	{
		return Hero->HeroData->AnimData.IdleWalkRunBS;
	}
	
	return nullptr;
}

UAimOffsetBlendSpace* UBaseAnimInstance::GetAimOffsetBS() const
{
	if (Hero && Hero->HeroData)
	{
		return Hero->HeroData->AnimData.AimOffsetBS;
	}

	return nullptr;
}

UAnimSequenceBase* UBaseAnimInstance::GetJumpStartAnim() const
{
	if (Hero && Hero->HeroData)
	{
		return Hero->HeroData->AnimData.JumpStartAnim;
	}

	return nullptr;
}

UAnimSequenceBase* UBaseAnimInstance::GetJumpLoopAnim() const
{
	if (Hero && Hero->HeroData)
	{
		return Hero->HeroData->AnimData.JumpLoopAnim;
	}

	return nullptr;
}

UAnimSequenceBase* UBaseAnimInstance::GetJumpEndAnim() const
{
	if (Hero && Hero->HeroData)
	{
		return Hero->HeroData->AnimData.JumpEndAnim;
	}

	return nullptr;
}
