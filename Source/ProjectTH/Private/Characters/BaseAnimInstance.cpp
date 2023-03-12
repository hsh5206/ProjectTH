// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "Characters/BaseHero.h"

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