// Copyright Serico Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UltimateCharacter.generated.h"

UCLASS()
class UDEMYULTIMATECOURSE_API AUltimateCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AUltimateCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	virtual void BeginPlay() override;
};
