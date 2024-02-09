// Copyright (c) 2024, Rob Meade. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "ImpactableInterface.generated.h"


UINTERFACE(MinimalAPI)
class UImpactableInterface : public UInterface
{
	GENERATED_BODY()
};


class ROBZANOID_API IImpactableInterface
{
	GENERATED_BODY()


public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Robzanoid|Interface")
	void Impact();

};
