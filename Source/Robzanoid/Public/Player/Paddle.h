// Copyright (c) 2024, Rob Meade. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Paddle.generated.h"


UCLASS()
class ROBZANOID_API APaddle : public APawn
{
	GENERATED_BODY()


public:

	APaddle();


protected:

	virtual void BeginPlay() override;


private:	

};
