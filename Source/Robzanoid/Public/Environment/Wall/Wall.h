// Copyright (c) 2024, Rob Meade. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Interfaces/ImpactableInterface.h"

#include "Wall.generated.h"


// Forward Declarations
class UBoxComponent;
class UStaticMeshComponent;


UCLASS()
class ROBZANOID_API AWall : public AActor, public IImpactableInterface
{
	GENERATED_BODY()


public:	

	AWall();


protected:

	virtual void BeginPlay() override;
	virtual void Impact_Implementation() override;

	UPROPERTY(VisibleAnywhere, Category = "Robzanoid|Components")
	TObjectPtr<UStaticMeshComponent> StaticMesh = nullptr;

};
