// Copyright (c) 2024, Rob Meade. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "PlaySpace.generated.h"


// Forward Declarations
class USceneComponent;

class USweeperComponent;
class UWallComponent;


UCLASS()
class ROBZANOID_API APlaySpace : public AActor
{
	GENERATED_BODY()


public:	

	APlaySpace();


protected:

	virtual void BeginPlay() override;


private:

	UPROPERTY(VisibleAnywhere, Category = "Robzanoid|Components")
	TObjectPtr<USceneComponent> SceneRoot = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Robzanoid|Components")
	TObjectPtr<UWallComponent> TopWall = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Robzanoid|Components")
	TObjectPtr<UWallComponent> LeftWall = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Robzanoid|Components")
	TObjectPtr<UWallComponent> RightWall = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Robzanoid|Components")
	TObjectPtr<USweeperComponent> Sweeper = nullptr;

};
