// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/TwinBlast_Missile_Projectile.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Characters/BaseHero.h"
#include "AbilitySystem/THAbilitySystemComponent.h"

void ATwinBlast_Missile_Projectile::OnBulletHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor == GetOwner()) return;

	if (ABaseHero* OwnerHero = Cast<ABaseHero>(GetOwner()))
	{
		FVector Start = Hit.Location;
		FVector End = Hit.Location;

		TArray<AActor*> IgnoreActors;
		IgnoreActors.Add(this);
		TArray<FHitResult> HitResults;

		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		TEnumAsByte<EObjectTypeQuery> Pawn = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn);
		ObjectTypes.Add(Pawn);

		UKismetSystemLibrary::SphereTraceMultiForObjects(
			this,
			Start,
			End,
			200.f,
			ObjectTypes,
			false,
			IgnoreActors,
			EDrawDebugTrace::None,
			HitResults,
			true
		);
		
		MultiSpawnEmitterAtLocation(Hit.ImpactPoint);
		MultiSpawnSoundAtLocation(Hit.ImpactPoint);

		if (HitResults.Num() != 0)
		{
			for (auto HitResult : HitResults)
			{
				if(IgnoreActors.Contains(HitResult.GetActor())) continue;

				if (ABaseHero* TargetHero = Cast<ABaseHero>(HitResult.GetActor()))
				{
					FGameplayEffectContextHandle EffectContext = OwnerHero->GetAbilitySystemComponent()->MakeEffectContext();
					EffectContext.AddHitResult(HitResult);
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

					IgnoreActors.AddUnique(HitResult.GetActor());

				}
			}
		}
		// Decal »ý¼º
		//MulticastSpawnDecal(Hit);
	}

	Destroy();
}

void ATwinBlast_Missile_Projectile::MultiSpawnSoundAtLocation_Implementation(const FVector& Location)
{
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ExplosionSound, Location);
}

void ATwinBlast_Missile_Projectile::MultiSpawnEmitterAtLocation_Implementation(const FVector& Location)
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticle, Location, FRotator(0), true);
}

void ATwinBlast_Missile_Projectile::BeginPlay()
{
	Super::BeginPlay();

	if (TracerComponent)
	{
		TracerComponent->SetWorldRotation(FRotator(GetActorRotation().Pitch, -GetActorRotation().Yaw, GetActorRotation().Roll));
	}
}
