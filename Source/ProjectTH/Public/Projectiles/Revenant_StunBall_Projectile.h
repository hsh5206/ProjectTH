// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectiles/BaseProjectile.h"
#include "Revenant_StunBall_Projectile.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTH_API ARevenant_StunBall_Projectile : public ABaseProjectile
{
	GENERATED_BODY()

public:
	virtual void OnBulletHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
	UPROPERTY(EditDefaultsOnly)
	class UParticleSystem* ExplosionParticle;
	UPROPERTY(EditDefaultsOnly)
	class USoundBase* ExplosionSound;

	UFUNCTION(NetMulticast, Reliable)
	void MultiSpawnSoundAtLocation(const FVector& Location);
	UFUNCTION(NetMulticast, Reliable)
	void MultiSpawnEmitterAtLocation(const FVector& Location);

protected:
	virtual void BeginPlay() override;
};
