// Copyright (c) 2024, Rob Meade. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "DeathZone.generated.h"


UCLASS()
class ROBZANOID_API ADeathZone : public AActor
{
	GENERATED_BODY()

	
public:	

	ADeathZone();


protected:

	virtual void BeginPlay() override;


private:

};
