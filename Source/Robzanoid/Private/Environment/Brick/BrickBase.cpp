// Copyright (c) 2024, Rob Meade. All rights reserved.

#include "Environment/Brick/BrickBase.h"

/*
 * Constructor
 */
ABrickBase::ABrickBase()
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
void ABrickBase::BeginPlay()
{
	Super::BeginPlay();

	SetDestructibilityAndStrength();
}


/*
 * Protected Methods
 */
void ABrickBase::Impact_Implementation()
{
	if (bIsIndestructible == false)
	{
		Strength--;

		if (Strength <= 0)
		{
			Destroy();
		}		
	}
}


/*
 * Private Methods
 */
void ABrickBase::SetDestructibilityAndStrength()
{
	switch (BrickType)
	{
		case EBrickType::DestructibleSingleHit:
		{
			bIsIndestructible = false;
			Strength = 1;
			break;
		}
		case EBrickType::DestructibleMultiHit:
		{
			bIsIndestructible = false;
			Strength = 2;
			break;
		}
		case EBrickType::Indestructible:
		{
			bIsIndestructible = true;
			Strength = 0;
			break;
		}
	}
}

