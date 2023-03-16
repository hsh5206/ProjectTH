// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/TwinBlast_Basic_Projectile.h"

#include "Characters/BaseHero.h"
#include "AbilitySystem/THAbilitySystemComponent.h"


void ATwinBlast_Basic_Projectile::OnBulletHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (ABaseHero* OwnerHero = Cast<ABaseHero>(GetOwner()))
	{
		if (ABaseHero* TargetHero = Cast<ABaseHero>(OtherActor))
		{

				FGameplayEffectContextHandle EffectContext = OwnerHero->GetAbilitySystemComponent()->MakeEffectContext();
				EffectContext.AddHitResult(Hit);
				FGameplayEffectSpecHandle SpecHandle = OwnerHero->GetAbilitySystemComponent()->MakeOutgoingSpec(HitEffectToTarget, 1, EffectContext);
				if (SpecHandle.IsValid())
				{
					FActiveGameplayEffectHandle ActiveGEHandle = OwnerHero->GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), TargetHero->GetAbilitySystemComponent());
				}
		}
		else
		{
			// Decal »ý¼º
			MulticastSpawnDecal(Hit);
		}
	}

	Destroy();
}
