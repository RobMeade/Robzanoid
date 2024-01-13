// Copyright (c) 2024, Rob Meade. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "BrickBase.generated.h"


UCLASS()
class ROBZANOID_API ABrickBase : public AActor
{
	GENERATED_BODY()


public:	

	ABrickBase();


protected:

	virtual void BeginPlay() override;


private:

};
