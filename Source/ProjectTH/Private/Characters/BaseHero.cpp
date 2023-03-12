// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseHero.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerState.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

#include "Frameworks/THPlayerState.h"
#include "AbilitySystem/THAbilitySystemComponent.h"
#include "AbilitySystem/THGameplayAbility.h"
#include "DataAssets/HeroData.h"

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

UTHAbilitySystemComponent* ABaseHero::GetAbilitySystemComponent()
{
	return Cast<UTHAbilitySystemComponent>(Cast<ATHPlayerState>(GetPlayerState())->GetAbilitySystemComponent());
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
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetPlayerState(), Payload.EventTag, Payload);
}

void ABaseHero::OnJumpActionEnd()
{
	// Stop Jumping
}

void ABaseHero::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	if (UTHAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponent())
	{
		FGameplayTagContainer Tag;
		Tag.AddTag(FGameplayTag::RequestGameplayTag(FName("State.Movement.Jump")));
		AbilitySystemComponent->RemoveActiveEffectsWithTags(Tag);
	}
}

void ABaseHero::InitializeAttributes()
{
	UTHAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponent();
	TArray<TSubclassOf<UGameplayEffect>> DefaultAttributeSettingEffects = HeroData->HeroASData.DefaultAttributeSettingEffects;
	if (AbilitySystemComponent)
	{
		for (auto DefaultAttributeEffect : DefaultAttributeSettingEffects)
		{
			FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
			EffectContext.AddSourceObject(this);

			FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributeEffect, 1, EffectContext);
			if (SpecHandle.IsValid())
			{
				FActiveGameplayEffectHandle GEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
			}
		}
	}
}

void ABaseHero::GiveAbilities()
{
	UTHAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponent();
	TArray<TSubclassOf<UTHGameplayAbility>> DefaultsAbilities = HeroData->HeroASData.DefaultsAbilities;
	if (HasAuthority() && AbilitySystemComponent)
	{
		for (TSubclassOf<UTHGameplayAbility>& StartupAbility : DefaultsAbilities)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(StartupAbility));
		}
	}
}

void ABaseHero::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// AbilitySystem의 owner와 avatar세팅
	GetAbilitySystemComponent()->InitAbilityActorInfo(GetPlayerState(), this);

	InitializeAttributes();
	GiveAbilities();
}

void ABaseHero::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	GetAbilitySystemComponent()->InitAbilityActorInfo(GetPlayerState(), this);
	InitializeAttributes();
}
