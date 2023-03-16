// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectiles/BaseProjectile.h"
#include "TwinBlaster_Ultimate_Projectile.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTH_API ATwinBlaster_Ultimate_Projectile : public ABaseProjectile
{
	GENERATED_BODY()
	
public:
	virtual void OnBulletHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

protected:
	virtual void BeginPlay() override;
};
