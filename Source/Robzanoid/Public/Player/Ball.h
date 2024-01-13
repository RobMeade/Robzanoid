// Copyright (c) 2024, Rob Meade. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Ball.generated.h"


UCLASS()
class ROBZANOID_API ABall : public AActor
{
	GENERATED_BODY()


public:	

	ABall();


protected:

	virtual void BeginPlay() override;


private:	

};
