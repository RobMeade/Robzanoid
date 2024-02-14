// Copyright (c) 2024, Rob Meade. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Interfaces/ImpactableInterface.h"

#include "WallComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROBZANOID_API UWallComponent : public UStaticMeshComponent, public IImpactableInterface
{
	GENERATED_BODY()


public:	

	explicit UWallComponent(const FObjectInitializer& ObjectInitializer);


protected:

	virtual void PostInitProperties() override;
	virtual void Impact_Implementation() override;

};
