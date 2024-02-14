// Copyright (c) 2024, Rob Meade. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"

#include "SweeperComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROBZANOID_API USweeperComponent : public UBoxComponent
{
	GENERATED_BODY()


public:	

	explicit USweeperComponent(const FObjectInitializer& ObjectInitializer);


protected:

	virtual void BeginPlay() override;


private:

	UFUNCTION()
	void OnCollisionBeginComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
