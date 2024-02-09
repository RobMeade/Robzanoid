// Copyright (c) 2024, Rob Meade. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Sweeper.generated.h"


// Forward Declarations
class UBoxComponent;


UCLASS()
class ROBZANOID_API ASweeper : public AActor
{
	GENERATED_BODY()

	
public:	

	ASweeper();


protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Robzanoid|Components")
	TObjectPtr<UBoxComponent> Collision;


private:

	UFUNCTION()
	void OnCollisionBeginComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
