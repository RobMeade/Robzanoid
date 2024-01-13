// Copyright (c) 2024, Rob Meade. All rights reserved.

#include "Environment/Brick/BrickBase.h"


ABrickBase::ABrickBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABrickBase::BeginPlay()
{
	Super::BeginPlay();	
}
