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
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* Camera;

	virtual class UTHAbilitySystemComponent* GetAbilitySystemComponent();

protected:
	virtual void BeginPlay() override;
	virtual void PawnClientRestart() override;

public:	
	/** Hero Data */
	UPROPERTY(EditDefaultsOnly)
	class UHeroData* HeroData;
	UFUNCTION(Server, Reliable)
	void ServerSetHeroData(const UHeroData* NewHeroData);
	void SetHeroData();

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
	UPROPERTY(EditDefaultsOnly)
	UInputAction* ReloadInputAction;
	UPROPERTY(EditDefaultsOnly)
	class UInputAction* OnSeeScroeAction;
	void SeeScore();
	void CancelSeeScore();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> ScoreWidgetClass;
	UUserWidget* ScoreWidget;

	/** Move */
	void OnMoveAction(const FInputActionValue& Value);
	/** Look */
	void OnLookAction(const FInputActionValue& Value);
	/** Jump */
	void OnJumpAction();
	virtual void Landed(const FHitResult& Hit) override;
	/** Basic Attack */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanBaseAttack = true;
	void OnBasicAttack();
	UPROPERTY(BlueprintReadOnly)
	FName SectionName = FName("L");
	UFUNCTION(BlueprintCallable, Server, Reliable)
	void ServerChangeSectionName();
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void MulticastChangeSectionName();
	/** Reload */
	void OnReload();

	/** Death */
	void Death();
	void Respawn();
	FTimerHandle DeathThenRespawnTimer;

	class UUserWidget* CrossHair;
	UFUNCTION(BlueprintCallable)
	void TraceToCrossHair();
	
	/** Projectile */
	UPROPERTY(BlueprintReadOnly)
	FVector CrossHairHitLocation;
	UFUNCTION(Server, Reliable)
	void ServerSetCrossHairHitLocation(const FHitResult& CrossHairHitResult);
	UFUNCTION(NetMulticast, Reliable)
	void MulticastSetCrossHairHitLocation(const FHitResult& CrossHairHitResult);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UWidgetComponent* HealthBarWidget;
	UFUNCTION(Server, Reliable)
	void ServerSetHPBarPercent(const float& CurrentHP, const float& MaxHP);
	UFUNCTION(NetMulticast, Reliable)
	void MulticastSetHPBarPercent(const float& CurrentHP, const float& MaxHP);

public:
	virtual void InitializeAttributes();
	virtual void GiveAbilities();

private:
	bool bIsBindASCInput = false;
};
