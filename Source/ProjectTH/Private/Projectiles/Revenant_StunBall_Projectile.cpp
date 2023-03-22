// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/Revenant_StunBall_Projectile.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerState.h"

#include "Characters/BaseHero.h"
#include "AbilitySystem/THAbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

void ARevenant_StunBall_Projectile::OnBulletHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
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
			100.f,
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
				if (IgnoreActors.Contains(HitResult.GetActor())) continue;

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

					//// Send Stun Event to Target
					//FGameplayEventData Payload;
					//Payload.Instigator = this;
					//Payload.EventTag = FGameplayTag::RequestGameplayTag(FName("Event.Ability.Stun"));
					//UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(TargetHero->GetPlayerState(), Payload.EventTag, Payload);

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

void ARevenant_StunBall_Projectile::MultiSpawnSoundAtLocation_Implementation(const FVector& Location)
{
	if (!ExplosionSound) return;

	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ExplosionSound, Location);
}

void ARevenant_StunBall_Projectile::MultiSpawnEmitterAtLocation_Implementation(const FVector& Location)
{
	if (!ExplosionParticle) return;

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticle, Location, FRotator(0), true);
}

void ARevenant_StunBall_Projectile::BeginPlay()
{
	Super::BeginPlay();

	if (TracerComponent)
	{
		// TracerComponent->SetWorldRotation(FRotator(GetActorRotation().Pitch, -GetActorRotation().Yaw, GetActorRotation().Roll));
		TracerComponent->SetWorldScale3D(FVector(1.5f, 1.5f, 1.5f));
	}
}
