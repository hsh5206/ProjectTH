// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/TwinBlaster_GA_MR_NitroShot.h"
#include "Engine/SkeletalMeshSocket.h"

#include "Characters/BaseHero.h"
#include "Projectiles/BaseProjectile.h"

void UTwinBlaster_GA_MR_NitroShot::FireL(const FVector& HitTarget)
{
	if (USkeletalMeshComponent* Mesh = Cast<ABaseHero>(GetActorInfo().AvatarActor)->GetMesh())
	{
		const USkeletalMeshSocket* MuzzleFlashSocket = Mesh->GetSocketByName(FName("Muzzle_BaseAttack_L"));
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
					World->SpawnActor<ABaseProjectile>(ProjectileClass, SocketTransform.GetLocation(), ToTarget.Rotation(), SpawnParams);
				}
			}
		}
	}
}

void UTwinBlaster_GA_MR_NitroShot::FireR(const FVector& HitTarget)
{
	if (USkeletalMeshComponent* Mesh = Cast<ABaseHero>(GetActorInfo().AvatarActor)->GetMesh())
	{
		const USkeletalMeshSocket* MuzzleFlashSocket = Mesh->GetSocketByName(FName("Muzzle_BaseAttack_R"));
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
					World->SpawnActor<ABaseProjectile>(ProjectileClass, SocketTransform.GetLocation(), ToTarget.Rotation(), SpawnParams);
				}
			}
		}
	}
}
