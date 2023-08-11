// Copyright Serico Games

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterTypes.h"
#include "GameFramework/Character.h"
#include "UltimateCharacter.generated.h"

class AItem;
class UCameraComponent;
class USpringArmComponent;
struct FInputActionValue;
class UInputAction;
class UInputComponent;
class UInputMappingContext;

UCLASS()
class UDEMYULTIMATECOURSE_API AUltimateCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AUltimateCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
protected:
	virtual void BeginPlay() override;

	/*
	 * Input Callbacks
	 */
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void EKeyPressed();
	void Attack();

	/*
	 * Play Montage Functions
	 */
	void PlayAttackMontage() const;
	bool CanAttack() const;
	
	UFUNCTION(BlueprintCallable)
	void AttackEnd();
private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> EquipAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> AttackAction;

	UPROPERTY(VisibleAnywhere, Category = "Character")
	TObjectPtr<USkeletalMeshComponent> CharacterMesh;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(VisibleInstanceOnly)
	TObjectPtr<AItem> OverlappingItem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EActionState ActionState = EActionState::EAS_Unoccupied;

	/*
	 * Animation montages
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	TObjectPtr<UAnimMontage> AttackMontage;

public:
	FORCEINLINE void SetOverlappingItem(AItem* Item) { OverlappingItem = Item; }
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }
};
