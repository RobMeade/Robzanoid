// Copyright (c) 2024, Rob Meade. All rights reserved.

#include "Environment/PlaySpace/PlaySpace.h"

#include "Environment/Sweeper/SweeperComponent.h"
#include "Environment/Wall/WallComponent.h"


/*
 * Constructor
 */
APlaySpace::APlaySpace()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	TopWall = CreateDefaultSubobject<UWallComponent>(TEXT("TopWall"));
	TopWall->SetupAttachment(SceneRoot);

	TopWall->SetRelativeLocation(FVector(0.0f, 0.0f, 1960.0f));
	TopWall->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
	TopWall->SetRelativeScale3D(FVector(0.8f, 0.8f, 22.4f));

	LeftWall = CreateDefaultSubobject<UWallComponent>(TEXT("LeftWall"));
	LeftWall->SetupAttachment(SceneRoot);

	LeftWall->SetRelativeLocation(FVector(-1080.0f, 0.0f, 1000.0f));
	LeftWall->SetRelativeScale3D(FVector(0.8f, 0.8f, 20.0f));

	RightWall = CreateDefaultSubobject<UWallComponent>(TEXT("RightWall"));
	RightWall->SetupAttachment(SceneRoot);

	RightWall->SetRelativeLocation(FVector(1080.0f, 0.0f, 1000.0f));
	RightWall->SetRelativeScale3D(FVector(0.8f, 0.8f, 20.0f));

	Sweeper = CreateDefaultSubobject<USweeperComponent>(TEXT("Sweeper"));
	Sweeper->SetupAttachment(SceneRoot);

	Sweeper->SetRelativeLocation(FVector(0.0f, 0.0f, -100.0f));
}


/*
 * Lifecycle Methods
 */
void APlaySpace::BeginPlay()
{
	Super::BeginPlay();	
}
