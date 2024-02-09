// Copyright (c) 2024, Rob Meade. All rights reserved.

#include "Environment/Wall/Wall.h"


/*
 * Constructor
 */
AWall::AWall()
{
 	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	StaticMesh->SetCollisionResponseToAllChannels(ECR_Block);

	SetRootComponent(StaticMesh);
}


/*
 * Lifecycle Methods
 */
void AWall::BeginPlay()
{
	Super::BeginPlay();
	
}


/*
 * Protected Methods
 */
void AWall::Impact_Implementation()
{
	// Note: Intentionally left blank
}
