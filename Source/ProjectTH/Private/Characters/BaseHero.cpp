// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseHero.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerState.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/WidgetComponent.h"
#include "Net/UnrealNetwork.h"
#include "Components/ProgressBar.h"
#include "Components/CapsuleComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

#include "Frameworks/THPlayerState.h"
#include "AbilitySystem/THAbilitySystemComponent.h"
#include "AbilitySystem/THGameplayAbility.h"
#include "DataAssets/HeroData.h"
#include "Projectiles/BaseProjectile.h"
#include "Widgets/Widget_HealthBar.h"
#include "AbilitySystem/THAttributeSet.h"
#include "Frameworks/THPlayerController.h"
#include "Frameworks/THGameMode.h"
#include "Frameworks/THHUD.h"
#include "../ProjectTH.h"

#include "DrawDebugHelpers.h"

#define TRACE_LENGTH 8000.f;

ABaseHero::ABaseHero()
{
	PrimaryActorTick.bCanEverTick = true;
	SetReplicates(true);
	SetReplicateMovement(true);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetMesh());
	SpringArm->TargetArmLength = 180.f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraLagSpeed = 30.f;
	SpringArm->SocketOffset = FVector(0.f, 70.f, 100.f);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;
	SpringArm->bUsePawnControlRotation = true;

	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 0.f, 1000.f);
	GetCharacterMovement()->MaxWalkSpeed = 500.f;

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -88.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, 0.f, -80.f));

	HealthBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	HealthBarWidget->SetupAttachment(GetRootComponent());
}

// Server
void ABaseHero::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (HealthBarWidget->GetWidget())
	{
		if (ATHPlayerState* THPS = Cast<ATHPlayerState>(GetPlayerState()))
		{
			Cast<UWidget_HealthBar>(HealthBarWidget->GetWidget())->SetHPBarPercent(THPS->GetAttributeSet()->GetHealth(), THPS->GetAttributeSet()->GetMaxHealth());
			ServerSetHPBarPercent(THPS->GetAttributeSet()->GetHealth(), THPS->GetAttributeSet()->GetMaxHealth());
		}
	}

	if (HeroData)
	{
		if (HeroData->CrossHairClass && IsLocallyControlled())
		{
			CrossHair = CreateWidget(GetWorld(), HeroData->CrossHairClass);
			CrossHair->AddToViewport();
		}
	}

	// AbilitySystem의 owner와 avatar세팅
	GetAbilitySystemComponent()->InitAbilityActorInfo(GetPlayerState(), this);

	InitializeAttributes();
	GiveAbilities();
}

// Client
void ABaseHero::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (HealthBarWidget->GetWidget())
	{
		if (ATHPlayerState* THPS = Cast<ATHPlayerState>(GetPlayerState()))
		{
			Cast<UWidget_HealthBar>(HealthBarWidget->GetWidget())->SetHPBarPercent(THPS->GetAttributeSet()->GetHealth(), THPS->GetAttributeSet()->GetMaxHealth());
			ServerSetHPBarPercent(THPS->GetAttributeSet()->GetHealth(), THPS->GetAttributeSet()->GetMaxHealth());
		}
	}

	if (HeroData && HeroData->CrossHairClass && IsLocallyControlled())
	{
		CrossHair = CreateWidget(GetWorld(), HeroData->CrossHairClass);
		CrossHair->AddToViewport();
	}

	GetAbilitySystemComponent()->InitAbilityActorInfo(GetPlayerState(), this);
	InitializeAttributes();

	if (GetPlayerState() && !bIsBindASCInput && InputComponent)
	{
		if (UAbilitySystemComponent* ASC = Cast<ATHPlayerState>(GetPlayerState())->GetAbilitySystemComponent())
		{
			ASC->BindAbilityActivationToInputComponent(
				InputComponent,
				FGameplayAbilityInputBinds(
					FString("ConfirmTarget"),
					FString("CancelTarget"),
					FString("ETHAbilityInputID"),
					static_cast<int32>(ETHAbilityInputID::Confirm),
					static_cast<int32>(ETHAbilityInputID::Cancel)
				)
			);

			bIsBindASCInput = true;
		}
	}
}

void ABaseHero::BeginPlay()
{
	Super::BeginPlay();

	if (!HasAuthority() && HealthBarWidget->GetWidget())
	{
		if (ATHPlayerState* THPS = Cast<ATHPlayerState>(GetPlayerState()))
		{
			Cast<UWidget_HealthBar>(HealthBarWidget->GetWidget())->SetHPBarPercent(THPS->GetAttributeSet()->GetHealth(), THPS->GetAttributeSet()->GetMaxHealth());
			ServerSetHPBarPercent(THPS->GetAttributeSet()->GetHealth(), THPS->GetAttributeSet()->GetMaxHealth());
		}
	}

}

void ABaseHero::PawnClientRestart()
{
	Super::PawnClientRestart();
	
	if (IsLocallyControlled())
	{
		Cast<ATHHUD>(Cast<ATHPlayerController>(GetController())->GetHUD())->DefaultBaseUISettingWhenSpawned();
	}

	/*if (ATHPlayerController* THPC = Cast<ATHPlayerController>(GetController()))
	{
		if (ATHHUD* THHUD = Cast<ATHHUD>(THPC->GetHUD()))
		{
			THHUD->SetSkillImages();
		}
	}*/

	if (GetController())
	{
		if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
			{
				Subsystem->ClearAllMappings();
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}
}

void ABaseHero::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME_CONDITION(ABaseHero, SectionName, COND_OwnerOnly);
}

UTHAbilitySystemComponent* ABaseHero::GetAbilitySystemComponent()
{
	return Cast<UTHAbilitySystemComponent>(Cast<ATHPlayerState>(GetPlayerState())->GetAbilitySystemComponent());
}

void ABaseHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ABaseHero::ServerSetHeroData_Implementation(const UHeroData* NewHeroData)
{
	HeroData->AnimData = NewHeroData->AnimData;
	HeroData->CrossHairClass = NewHeroData->CrossHairClass;
	HeroData->HeroASData = NewHeroData->HeroASData;
	HeroData->HeroSkillData = NewHeroData->HeroSkillData;
}

void ABaseHero::SetHeroData()
{
	ServerSetHeroData(HeroData);
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
		}
		if (BasicAttackInputAction)
		{
			PlayerEnhancedInputComponent->BindAction(BasicAttackInputAction, ETriggerEvent::Triggered, this, &ABaseHero::OnBasicAttack);
		}
		if (ReloadInputAction)
		{
			PlayerEnhancedInputComponent->BindAction(ReloadInputAction, ETriggerEvent::Started, this, &ABaseHero::OnReload);
		}
		if (OnSeeScroeAction)
		{
			PlayerEnhancedInputComponent->BindAction(OnSeeScroeAction, ETriggerEvent::Started, this, &ABaseHero::SeeScore);
			PlayerEnhancedInputComponent->BindAction(OnSeeScroeAction, ETriggerEvent::Completed, this, &ABaseHero::CancelSeeScore);
		}
	}

	if (GetPlayerState() && !bIsBindASCInput)
	{
		if (UAbilitySystemComponent* ASC = Cast<ATHPlayerState>(GetPlayerState())->GetAbilitySystemComponent())
		{
			ASC->BindAbilityActivationToInputComponent(
				InputComponent,
				FGameplayAbilityInputBinds(
					FString("ConfirmTarget"),
					FString("CancelTarget"),
					FString("ETHAbilityInputID"),
					static_cast<int32>(ETHAbilityInputID::Confirm),
					static_cast<int32>(ETHAbilityInputID::Cancel)
				)
			);

			bIsBindASCInput = true;
		}
	}
}

void ABaseHero::OnMoveAction(const FInputActionValue& Value)
{
	FGameplayTagContainer OwnedTags;
	GetAbilitySystemComponent()->GetOwnedGameplayTags(OwnedTags);
	if (OwnedTags.HasTag(FGameplayTag::RequestGameplayTag(FName("Ability.Movement.Stun")))) return;

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

void ABaseHero::OnBasicAttack()
{
	if (!bCanBaseAttack) return;

	TraceToCrossHair();

	if (IsLocallyControlled())
	{
		FGameplayEventData Payload;
		Payload.Instigator = this;
		Payload.EventTag = FGameplayTag::RequestGameplayTag(FName("Event.Attack.BasicAttack"));
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetPlayerState(), Payload.EventTag, Payload);
	}
}

void ABaseHero::ServerChangeSectionName_Implementation()
{
	MulticastChangeSectionName();
}

void ABaseHero::MulticastChangeSectionName_Implementation()
{
	SectionName = SectionName == FName("L") ? FName("R") : FName("L");
}

void ABaseHero::OnReload()
{
	if (IsLocallyControlled())
	{
		FGameplayEventData Payload;
		Payload.Instigator = this;
		Payload.EventTag = FGameplayTag::RequestGameplayTag(FName("Event.Movement.Reload"));
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetPlayerState(), Payload.EventTag, Payload);
	}
}

void ABaseHero::Death()
{
	//GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionProfileName(FName("Ragdoll"));
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->AddImpulse(FVector(0.f, 0.f, 5000.f));
	GetCharacterMovement()->DisableMovement();

	if(IsLocallyControlled()) CrossHair->RemoveFromParent();

	GetWorldTimerManager().SetTimer(DeathThenRespawnTimer, this, &ABaseHero::Respawn, .5f, false);
}

void ABaseHero::Respawn()
{
	if(IsLocallyControlled()) Cast<ATHPlayerController>(GetController())->Death();
}

void ABaseHero::SeeScore()
{
	if (!ScoreWidget && ScoreWidgetClass)
	{
		ScoreWidget = CreateWidget(GetWorld(), ScoreWidgetClass);
	}
	if(ScoreWidget) ScoreWidget->AddToViewport();
}

void ABaseHero::CancelSeeScore()
{
	if (ScoreWidget) ScoreWidget->RemoveFromParent();
}

void ABaseHero::TraceToCrossHair()
{
	FVector2D ViewportSize;
	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(ViewportSize);
	}

	FVector2D CrossHairLocation(ViewportSize.X / 2.f, ViewportSize.Y / 2.f);
	FVector CrossHairWorldPosition;
	FVector CrossHairWorldDirection;

	bool bScreenToWorldSuccessed = UGameplayStatics::DeprojectScreenToWorld(
		Cast<APlayerController>(GetController()),
		CrossHairLocation,
		CrossHairWorldPosition,
		CrossHairWorldDirection
	);

	if (bScreenToWorldSuccessed)
	{
		FVector Start = CrossHairWorldPosition;
		FVector End = Start + CrossHairWorldDirection * TRACE_LENGTH;

		FHitResult HitReslut;
		GetWorld()->LineTraceSingleByChannel(
			HitReslut,
			Start,
			End,
			ECollisionChannel::ECC_Visibility
		);

		if (!HitReslut.bBlockingHit)
		{
			HitReslut.ImpactPoint = End;
		}
		else
		{
			//DrawDebugSphere(GetWorld(), TraceHitResult.ImpactPoint, 12.f, 12, FColor::Red);
		}

		ServerSetCrossHairHitLocation(HitReslut);
	}
}

void ABaseHero::ServerSetCrossHairHitLocation_Implementation(const FHitResult& TraceHitResult)
{
	MulticastSetCrossHairHitLocation(TraceHitResult);
}

void ABaseHero::MulticastSetCrossHairHitLocation_Implementation(const FHitResult& TraceHitResult)
{
	CrossHairHitLocation = TraceHitResult.ImpactPoint;
}

void ABaseHero::ServerSetHPBarPercent_Implementation(const float& CurrentHP, const float& MaxHP)
{
	MulticastSetHPBarPercent(CurrentHP, MaxHP);
}

void ABaseHero::MulticastSetHPBarPercent_Implementation(const float& CurrentHP, const float& MaxHP)
{
	Cast<UWidget_HealthBar>(HealthBarWidget->GetWidget())->SetHPBarPercent(CurrentHP, MaxHP);
}

/** AbilitySystem */
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
