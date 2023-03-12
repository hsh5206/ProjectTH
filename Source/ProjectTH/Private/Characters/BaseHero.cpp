// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseHero.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

ABaseHero::ABaseHero()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 180.f;
	SpringArm->SetRelativeLocation(FVector(0.f, 70.f, 70.f));
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraLagSpeed = 5.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;
	SpringArm->bUsePawnControlRotation = true;

	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 0.f, 1000.f);
}

void ABaseHero::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseHero::PawnClientRestart()
{
	Super::PawnClientRestart();

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ABaseHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (MoveInputAction)
		{
			PlayerEnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &ABaseHero::OnMoveAction);
		}
		if (LookInputAction)
		{
			PlayerEnhancedInputComponent->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &ABaseHero::OnLookAction);
		}
		if (JumpInputAction)
		{
			PlayerEnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Started, this, &ABaseHero::OnJumpAction);
			PlayerEnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Completed, this, &ABaseHero::OnJumpActionEnd);
		}
	}
}

void ABaseHero::OnMoveAction(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ABaseHero::OnLookAction(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ABaseHero::OnJumpAction()
{
	FGameplayEventData Payload;
	Payload.Instigator = this;
	Payload.EventTag = FGameplayTag::RequestGameplayTag(FName("Event.Movement.Jump"));
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, Payload.EventTag, Payload);
}

void ABaseHero::OnJumpActionEnd()
{
	// Stop Jumping
}

void ABaseHero::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	//if (AbilitySystemComponent)
	//{
	//	AbilitySystemComponent->RemoveActiveEffectsWithTags(InAirTag);
	//}
}
