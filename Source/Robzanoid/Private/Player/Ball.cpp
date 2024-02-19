// Copyright (c) 2024, Rob Meade. All rights reserved.

#include "Player/Ball.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Interfaces/ImpactableInterface.h"


/*
 * Constructor
 */
ABall::ABall()
{
	PrimaryActorTick.bCanEverTick = false;

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetEnableGravity(false);
	Sphere->SetGenerateOverlapEvents(true);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	Sphere->SetCollisionResponseToAllChannels(ECR_Block);
	Sphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECR_Ignore);
	Sphere->SetUseCCD(true);
	SetRootComponent(Sphere);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(Sphere);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->InitialSpeed = 0.0f;
	ProjectileMovement->MaxSpeed = 3500.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->Bounciness = 1.0f;
	ProjectileMovement->Friction = 0.0f;
	ProjectileMovement->MaxSimulationIterations = 12;
	ProjectileMovement->bInterpMovement = true;
	ProjectileMovement->bInterpRotation = true;
	ProjectileMovement->Velocity = FVector::ZeroVector;
	ProjectileMovement->SetPlaneConstraintNormal(FVector(0.0f, 1.0f, 0.0f));
	ProjectileMovement->bConstrainToPlane = true;
}

void ABall::Launch(const float& InitialSpeed) const
{
	if (ProjectileMovement)
	{
		ProjectileMovement->InitialSpeed = InitialSpeed;
		ProjectileMovement->Velocity = FVector::UpVector * InitialSpeed;
	}
}


/*
 * Lifecycle Methods
 */
void ABall::BeginPlay()
{
	Super::BeginPlay();

	if (Sphere)
	{
		Sphere->OnComponentHit.AddDynamic(this, &ABall::OnSphereComponentHit);
	}
}


/*
 * Private Methods
 */
void ABall::OnSphereComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (IImpactableInterface* ImpactableInterface = Cast<IImpactableInterface>(OtherActor))
	{
		IImpactableInterface::Execute_Impact(OtherActor);
	}
}
