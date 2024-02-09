// Copyright (c) 2024, Rob Meade. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "CommonTypes/CommonTypes.h"
#include "Interfaces/ImpactableInterface.h"

#include "BrickBase.generated.h"


UCLASS()
class ROBZANOID_API ABrickBase : public AActor, public IImpactableInterface
{
	GENERATED_BODY()


public:	

	ABrickBase();

	EBrickType GetBrickType() const { return BrickType; }
	int32 GetPoints() const { return Points; }
	int32 GetStrength() const { return Strength; }
	void SetStrength(const int32 InStrength) { Strength = InStrength; }


protected:

	virtual void BeginPlay() override;
	virtual void Impact_Implementation() override;

	UPROPERTY(VisibleAnywhere, Category = "Robzanoid|Components")
	TObjectPtr<UStaticMeshComponent> StaticMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Robzanoid|Brick Properties")
	EBrickType BrickType = EBrickType::DestructibleSingleHit;

	UPROPERTY(EditDefaultsOnly, Category = "Robzanoid|Brick Properties")
	int32 Points = 50;


private:

	void SetDestructibilityAndStrength();

	int32 Strength = 1;
	bool bIsIndestructible = false;

};
