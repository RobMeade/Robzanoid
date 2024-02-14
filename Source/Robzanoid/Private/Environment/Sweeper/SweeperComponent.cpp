// Copyright (c) 2024, Rob Meade. All rights reserved.

#include "Environment/Sweeper/SweeperComponent.h"

#include "Components/BoxComponent.h"


/*
 * Constructor
 */
USweeperComponent::USweeperComponent(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;

	BoxExtent = FVector(1120.0f, 100.0f, 100.0f);
}


/*
 * Lifecycle Methods
 */
void USweeperComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &USweeperComponent::OnCollisionBeginComponentOverlap);
}


/*
 * Private Methods
 */
void USweeperComponent::OnCollisionBeginComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		OtherActor->Destroy();
	}
}
