// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/Revenant_GA_ChargeShot.h"
#include "Engine/SkeletalMeshSocket.h"

#include "Characters/BaseHero.h"
#include "Projectiles/BaseProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

void URevenant_GA_ChargeShot::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	GetOwningActorFromActorInfo()->GetWorldTimerManager().SetTimer(StackTimer, this, &URevenant_GA_ChargeShot::StackUp, .1f, false);

}

void URevenant_GA_ChargeShot::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);


}

void URevenant_GA_ChargeShot::StackUp()
{
	Stack++;
}

void URevenant_GA_ChargeShot::Fire(const FVector& HitTarget)
{
	GetOwningActorFromActorInfo()->GetWorldTimerManager().ClearTimer(StackTimer);

	if (USkeletalMeshComponent* Mesh = Cast<ABaseHero>(GetActorInfo().AvatarActor)->GetMesh())
	{
		const USkeletalMeshSocket* MuzzleFlashSocket = Mesh->GetSocketByName(FName("Muzzle_ChargeShot"));
		if (MuzzleFlashSocket)
		{
			FTransform SocketTransform = MuzzleFlashSocket->GetSocketTransform(Mesh);
			FVector ToTarget = HitTarget - SocketTransform.GetLocation(); // from Muzzle to HitLocation(CrossHair)
			if (ProjectileClass)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = GetActorInfo().AvatarActor.Get();
				SpawnParams.Instigator = Cast<APawn>(GetActorInfo().AvatarActor.Get());

				if (UWorld* World = GetWorld())
				{
					auto Projectile = World->SpawnActor<ABaseProjectile>(ProjectileClass, SocketTransform.GetLocation(), ToTarget.Rotation(), SpawnParams);
					Projectile->ProjectileMovementComponent->InitialSpeed = 5000.f;
					Projectile->ProjectileMovementComponent->MaxSpeed = 5000.f;
					Projectile->ProjectileMovementComponent->InitialSpeed += (2500.f * Stack);
					Projectile->ProjectileMovementComponent->MaxSpeed += (2500.f * Stack);
				}
			}
		}
	}
}
