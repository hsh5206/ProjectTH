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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UBoxComponent* BulletCollision;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditDefaultsOnly)
	class UParticleSystem* Tracer;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UParticleSystemComponent* TracerComponent;

	UPROPERTY(EditDefaultsOnly)
	class UMaterialInterface* BulletHoleDecal;
	UFUNCTION(NetMulticast, Reliable)
	void MulticastSpawnDecal(const FHitResult& Hit);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf <class UGameplayEffect> HitEffectToTarget;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf <class UGameplayEffect> HitEffectToSelf;

protected:
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable)
	virtual void OnBulletHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
