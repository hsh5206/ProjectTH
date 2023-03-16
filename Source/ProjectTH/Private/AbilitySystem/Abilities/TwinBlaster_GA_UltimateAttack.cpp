// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/TwinBlaster_GA_UltimateAttack.h"
#include "Engine/SkeletalMeshSocket.h"

#include "Characters/BaseHero.h"
#include "Projectiles/BaseProjectile.h"

void UTwinBlaster_GA_UltimateAttack::Fire(const FVector& HitTarget)
{
	if (USkeletalMeshComponent* Mesh = Cast<ABaseHero>(GetActorInfo().AvatarActor)->GetMesh())
	{
		const USkeletalMeshSocket* MuzzleFlashSocket = Mesh->GetSocketByName(FName("Muzzle_ChargedBlast"));
		if (MuzzleFlashSocket)
		{
			FTransform SocketTransform = MuzzleFlashSocket->GetSocketTransform(Mesh);
			FVector ToTarget = HitTarget - SocketTransform.GetLocation(); // from Muzzle to HitLocation(CrossHair)

			FVector Location = SocketTransform.GetLocation();

			if (ProjectileClass)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = GetActorInfo().AvatarActor.Get();
				SpawnParams.Instigator = Cast<APawn>(GetActorInfo().AvatarActor.Get());

				if (UWorld* World = GetWorld())
				{
					World->SpawnActor<ABaseProjectile>(ProjectileClass, Location, ToTarget.Rotation(), SpawnParams);
				}
			}
		}
	}
}