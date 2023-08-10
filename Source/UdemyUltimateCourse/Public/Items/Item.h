// Copyright Serico Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class UDEMYULTIMATECOURSE_API AItem : public AActor
{
	GENERATED_BODY()
	
public:
	AItem();
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
private:
	float RunningTime;
	float Amplitude = 0.25f;
	float TimeConstant = 5.f;
};
