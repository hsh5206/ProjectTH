// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
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

protected:
	virtual void BeginPlay() override;
	virtual void PawnClientRestart() override;

public:	
	/** Enhanced Input */
	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditDefaultsOnly)
	UInputAction* MoveInputAction;
	UPROPERTY(EditDefaultsOnly)
	UInputAction* LookInputAction;
	UPROPERTY(EditDefaultsOnly)
	UInputAction* JumpInputAction;

	/** Move */
	void OnMoveAction(const FInputActionValue& Value);
	/** Look */
	void OnLookAction(const FInputActionValue& Value);
	/** Jump */
	void OnJumpAction();
	void OnJumpActionEnd();
	virtual void Landed(const FHitResult& Hit) override;

};
