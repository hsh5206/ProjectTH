// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "THTypes.h"
#include "BaseHero.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class PROJECTTH_API ABaseHero : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseHero();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = Camera)
	class USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere, Category = Camera)
	class UCameraComponent* Camera;

	virtual class UTHAbilitySystemComponent* GetAbilitySystemComponent();

protected:
	virtual void BeginPlay() override;
	virtual void PawnClientRestart() override;

public:	
	/** Hero Data */
	UPROPERTY(EditDefaultsOnly)
	class UHeroData* HeroData;

	/** Enhanced Input */
	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditDefaultsOnly)
	UInputAction* MoveInputAction;
	UPROPERTY(EditDefaultsOnly)
	UInputAction* LookInputAction;
	UPROPERTY(EditDefaultsOnly)
	UInputAction* JumpInputAction;
	UPROPERTY(EditDefaultsOnly)
	UInputAction* BasicAttackInputAction;

	/** Move */
	void OnMoveAction(const FInputActionValue& Value);
	/** Look */
	void OnLookAction(const FInputActionValue& Value);
	/** Jump */
	void OnJumpAction();
	virtual void Landed(const FHitResult& Hit) override;
	/** Basic Attack */
	void OnBasicAttack();
	UPROPERTY(BlueprintReadOnly)
	FName SectionName = FName("L");

	void TraceToCrossHair(FHitResult& TraceHitResult);
	
	/** Projectile */
	UPROPERTY(BlueprintReadOnly)
	FHitResult CrossHairHitResult;

public:
	virtual void InitializeAttributes();
	virtual void GiveAbilities();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
};
