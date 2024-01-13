// Copyright (c) 2024, Rob Meade. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Wall.generated.h"


UCLASS()
class ROBZANOID_API AWall : public AActor
{
	GENERATED_BODY()


public:	

	AWall();


protected:

	virtual void BeginPlay() override;


private:	

};
