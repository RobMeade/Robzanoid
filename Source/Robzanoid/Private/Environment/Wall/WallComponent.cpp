// Copyright (c) 2024, Rob Meade. All rights reserved.

#include "Environment/Wall/WallComponent.h"


/*
 * Constructor
 */
UWallComponent::UWallComponent(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;
}


/*
 * Lifecycle Methods
 */
void UWallComponent::PostInitProperties()
{
	Super::PostInitProperties();

	SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	SetCollisionResponseToAllChannels(ECR_Block);
}


/*
 * Protected Methods
 */
void UWallComponent::Impact_Implementation()
{
	// Intentionally left empty
}
