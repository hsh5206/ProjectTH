// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProjectile.generated.h"

UCLASS()
class PROJECTTH_API ABaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseProjectile();
	virtual void Tick(float DeltaTime) override;
	virtual void Destroyed() override;

	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* BulletCollision;
	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditDefaultsOnly)
	class UParticleSystem* Tracer;
	class UParticleSystemComponent* TracerComponent;

	UPROPERTY(EditDefaultsOnly)
	class UMaterialInterface* BulletHoleDecal;
	UFUNCTION(NetMulticast, Reliable)
	void MulticastSpawnDecal(const FHitResult& Hit);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf <class UGameplayEffect> HitEffectToTarget;
protected:
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
	void OnBulletHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
