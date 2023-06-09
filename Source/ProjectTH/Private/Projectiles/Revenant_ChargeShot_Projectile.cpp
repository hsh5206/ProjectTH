// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/Revenant_ChargeShot_Projectile.h"
#include "Particles/ParticleSystemComponent.h"

#include "Characters/BaseHero.h"
#include "AbilitySystem/THAbilitySystemComponent.h"

void ARevenant_ChargeShot_Projectile::OnBulletHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnBulletHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);

	if (OtherActor == GetOwner()) return;

	if (ABaseHero* OwnerHero = Cast<ABaseHero>(GetOwner()))
	{
		if (ABaseHero* TargetHero = Cast<ABaseHero>(OtherActor))
		{
			FGameplayEffectContextHandle EffectContext = OwnerHero->GetAbilitySystemComponent()->MakeEffectContext();
			EffectContext.AddHitResult(Hit);
			EffectContext.AddInstigator(OwnerHero, OwnerHero);
			FGameplayEffectSpecHandle SpecHandle = OwnerHero->GetAbilitySystemComponent()->MakeOutgoingSpec(HitEffectToTarget, 1, EffectContext);
			if (SpecHandle.IsValid())
			{
				FActiveGameplayEffectHandle ActiveGEHandle = OwnerHero->GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), TargetHero->GetAbilitySystemComponent());
			}

			FGameplayEffectContextHandle EffectContextToSelf = OwnerHero->GetAbilitySystemComponent()->MakeEffectContext();
			FGameplayEffectSpecHandle SpecHandleToSelf = OwnerHero->GetAbilitySystemComponent()->MakeOutgoingSpec(HitEffectToSelf, 1, EffectContextToSelf);
			if (SpecHandleToSelf.IsValid())
			{
				FActiveGameplayEffectHandle ActiveGEHandleSelf = OwnerHero->GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*SpecHandleToSelf.Data.Get());
			}

		}
	}

	Destroy();
}

void ARevenant_ChargeShot_Projectile::BeginPlay()
{
	Super::BeginPlay();

	//SetActorRelativeRotation(FRotator(180.f, 0.f, 0.f));
	//SetActorRelativeLocation(FVector(300.f, 0.f, 0.f));

	if (TracerComponent)
	{
		TracerComponent->SetWorldScale3D(FVector(20.f, 20.f, 20.f));
	}
	//TracerComponent->SetWorldRotation(FRotator(-GetActorRotation().Pitch, -GetActorRotation().Yaw, -GetActorRotation().Roll));
}