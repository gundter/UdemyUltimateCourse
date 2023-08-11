// Copyright Serico Games


#include "Character/UltimateAnimInstance.h"

#include "Character/UltimateCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UUltimateAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	CharacterRef = Cast<AUltimateCharacter>(TryGetPawnOwner());
	if (CharacterRef)
	{
		CharacterMovement = CharacterRef->GetCharacterMovement();
	}
	
}

void UUltimateAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (CharacterMovement == nullptr) return;
	
	Velocity = CharacterMovement->Velocity;
	GroundSpeed = UKismetMathLibrary::VSizeXY(Velocity);
	bIsFalling = CharacterMovement->IsFalling();
	bShouldMove = GroundSpeed > 3.f && CharacterMovement->GetCurrentAcceleration() != FVector::ZeroVector;
	CharacterState = CharacterRef->GetCharacterState();
}
