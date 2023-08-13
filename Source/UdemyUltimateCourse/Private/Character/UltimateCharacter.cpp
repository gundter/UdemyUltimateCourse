// Copyright Serico Games


#include "Character/UltimateCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Item/Weapon/Weapon.h"

AUltimateCharacter::AUltimateCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.);
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;

	CharacterMesh = CreateDefaultSubobject<USkeletalMeshComponent>("CharacterMesh");
	CharacterMesh->SetupAttachment(GetMesh());

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 300.f;
	CameraBoom->SocketOffset = FVector(0.f, 75.f, 50.f);
	CameraBoom->bUsePawnControlRotation = true;
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

void AUltimateCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (const APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultContext, 0);	
		}
	}
}

void AUltimateCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AUltimateCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AUltimateCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(PickupAction, ETriggerEvent::Started, this, &AUltimateCharacter::PickupItem);
		EnhancedInputComponent->BindAction(EquipAction, ETriggerEvent::Started, this, &AUltimateCharacter::EquipWeapon);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AUltimateCharacter::Attack);
	}
}

void AUltimateCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUltimateCharacter::Move(const FInputActionValue& Value)
{
	if (ActionState == EActionState::EAS_Attacking) return;
	
	// input is a Vector2D
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AUltimateCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AUltimateCharacter::PickupItem()
{
	if (AWeapon* OverlappingWeapon = Cast<AWeapon>(OverlappingItem))
	{
		OverlappingWeapon->Equip(CharacterMesh, "RightHandSocket");
		CharacterState = ECharacterState::ECS_EquippedOneHandedWeapon;
		EquippedWeapon = OverlappingWeapon;
	}
}

void AUltimateCharacter::EquipWeapon()
{
	if (CanDisarm())
	{
		PlayEquipMontage("Unequip");
		CharacterState = ECharacterState::ECS_Unequipped;
	}
	else if (CanArm())
	{
		PlayEquipMontage("Equip");
		CharacterState = ECharacterState::ECS_EquippedOneHandedWeapon;
	}
}

void AUltimateCharacter::Attack()
{
	if (CanAttack())
	{
		PlayAttackMontage();
		ActionState = EActionState::EAS_Attacking;
	}
}

bool AUltimateCharacter::CanAttack() const
{
	return ActionState == EActionState::EAS_Unoccupied &&
		CharacterState != ECharacterState::ECS_Unequipped;
}

bool AUltimateCharacter::CanDisarm() const
{
	return ActionState == EActionState::EAS_Unoccupied &&
			CharacterState != ECharacterState::ECS_Unequipped;
}

bool AUltimateCharacter::CanArm() const
{
	return ActionState == EActionState::EAS_Unoccupied &&
		CharacterState == ECharacterState::ECS_Unequipped &&
			EquippedWeapon;
}

void AUltimateCharacter::Disarm()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->AttachMeshToSocket(CharacterMesh, "HolsterSocket");
	}
}

void AUltimateCharacter::PlayAttackMontage() const
{
	if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance(); AnimInstance && AttackMontage)
	{
		AnimInstance->Montage_Play(AttackMontage);
		const int32 Selection = FMath::RandRange(0, 1);
		FName SectionName = FName();
		switch (Selection)
		{
		case 0:
			SectionName = "Attack1";
			break;
		case 1:
			SectionName = "Attack2";
			break;
		default:
			break;
		}

		AnimInstance->Montage_JumpToSection(SectionName, AttackMontage);
	}
}

void AUltimateCharacter::PlayEquipMontage(const FName SectionName) const
{
	if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance(); AnimInstance && EquipMontage)
	{
		AnimInstance->Montage_Play(EquipMontage);
		AnimInstance->Montage_JumpToSection(SectionName, EquipMontage);
	}
}

void AUltimateCharacter::AttackEnd()
{
	ActionState = EActionState::EAS_Unoccupied;
}
