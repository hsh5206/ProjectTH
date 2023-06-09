// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/BaseProjectile.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"

#include "AbilitySystem/THAbilitySystemComponent.h"
#include "Characters/BaseHero.h"

ABaseProjectile::ABaseProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	SetReplicateMovement(true);

	BulletCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	SetRootComponent(BulletCollision);
	BulletCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	BulletCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BulletCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BulletCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	BulletCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
	BulletCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	BulletCollision->IgnoreActorWhenMoving(GetOwner(), true);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
}

void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	if (Tracer)
	{
		TracerComponent = UGameplayStatics::SpawnEmitterAttached(
			Tracer,
			BulletCollision,
			FName(),
			GetActorLocation(),
			GetActorRotation(),
			EAttachLocation::KeepWorldPosition
		);
	}

	if (HasAuthority())
	{
		BulletCollision->OnComponentHit.AddDynamic(this, &ThisClass::OnBulletHit);
	}
}

void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseProjectile::OnBulletHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

}

void ABaseProjectile::MulticastSpawnDecal_Implementation(const FHitResult& Hit)
{
	UGameplayStatics::SpawnDecalAttached(BulletHoleDecal, FVector(30.f, 30.f, 30.f), Hit.Component.Get(), NAME_None, Hit.Location, UKismetMathLibrary::MakeRotFromX(Hit.ImpactNormal), EAttachLocation::KeepWorldPosition);
}

void ABaseProjectile::Destroyed()
{

	Super::Destroyed();
}

