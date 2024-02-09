// Copyright (c) 2024, Rob Meade. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Ball.generated.h"


// Forward Declarations
class UProjectileMovementComponent;
class USphereComponent;
class UStaticMeshComponent;


UCLASS(Blueprintable)
class ROBZANOID_API ABall : public AActor
{
	GENERATED_BODY()


public:	

	ABall();


protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Robzanoid|Components")
	TObjectPtr<USphereComponent> Sphere = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Robzanoid|Components")
	TObjectPtr<UStaticMeshComponent> StaticMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Robzanoid|Components")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;


private:

	UFUNCTION()
	void OnSphereComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
};
