// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/TwinBlast_GA_BasicAttack.h"
#include "Engine/SkeletalMeshSocket.h"

#include "Characters/BaseHero.h"
#include "Projectiles/BaseProjectile.h"

void UTwinBlast_GA_BasicAttack::FireL(const FVector& HitTarget)
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

void UTwinBlast_GA_BasicAttack::FireR(const FVector& HitTarget)
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