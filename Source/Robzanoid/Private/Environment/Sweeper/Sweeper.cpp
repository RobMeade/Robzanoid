// Copyright (c) 2024, Rob Meade. All rights reserved.

#include "Environment/Sweeper/Sweeper.h"

#include "Components/BoxComponent.h"


/*
 * Constructor
 */
ASweeper::ASweeper()
{
	PrimaryActorTick.bCanEverTick = false;

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collision->SetBoxExtent(FVector(1120.0f, 100.0f, 100.0f));

	SetRootComponent(Collision);
}


/*
 * Lifecycle Methods
 */
void ASweeper::BeginPlay()
{
	Super::BeginPlay();

	if (Collision)
	{
		Collision->OnComponentBeginOverlap.AddDynamic(this, &ASweeper::OnCollisionBeginComponentOverlap);
	}
}


/*
 * Private Methods
 */
void ASweeper::OnCollisionBeginComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		OtherActor->Destroy();
	}
}
