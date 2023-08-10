// Copyright Serico Games


#include "Items/Item.h"
#include "UdemyUltimateCourse/DebugMacros.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	const FVector Location = GetActorLocation();
	const FVector Forward = GetActorForwardVector();

	DRAW_SPHERE(Location)
	DRAW_VECTOR(Location, Location + Forward * 100)
	
	
	DRAW_SPHERE(Location)
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

