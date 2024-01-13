// Copyright (c) 2024, Rob Meade. All rights reserved.

#include "Environment/DeathZone/DeathZone.h"


ADeathZone::ADeathZone()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ADeathZone::BeginPlay()
{
	Super::BeginPlay();	
}
