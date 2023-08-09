// Copyright Serico Games


#include "Character/UltimateCharacterBase.h"

// Sets default values
AUltimateCharacterBase::AUltimateCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUltimateCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUltimateCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AUltimateCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

