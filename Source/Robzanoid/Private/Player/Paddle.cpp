// Copyright (c) 2024, Rob Meade. All rights reserved.

#include "Player/Paddle.h"

#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SplineComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Game/RobzanoidGameInstance.h"
#include "Player/Ball.h"


/*
 * Constructor
 */
APaddle::APaddle()
{
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>("DefaultSceneRoot");
	SetRootComponent(DefaultSceneRoot);

	PaddleAnchor = CreateDefaultSubobject<USceneComponent>("PaddleAnchor");
	PaddleAnchor->SetupAttachment(DefaultSceneRoot);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(PaddleAnchor);
	StaticMesh->SetGenerateOverlapEvents(false);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Capsule = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	Capsule->SetupAttachment(PaddleAnchor);
	Capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Capsule->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	LaunchPosition = CreateDefaultSubobject<UArrowComponent>("LaunchPosition");
	LaunchPosition->SetupAttachment(PaddleAnchor);
	LaunchPosition->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));

	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
	Spline->SetupAttachment(DefaultSceneRoot);
	Spline->SetSelectedSplineSegmentColor(FLinearColor(0.828f, 0.364f, 0.003));

	Spline->ClearSplinePoints();

	const FVector SplinePoint1 = FVector(-625.0f, 0.0f, 0.0f);
	Spline->AddSplinePoint(SplinePoint1, ESplineCoordinateSpace::Local, false);
	Spline->SetTangentAtSplinePoint(0, FVector::ZeroVector, ESplineCoordinateSpace::Local, false);
	Spline->SetSplinePointType(0, ESplinePointType::Linear);

	const FVector SplinePoint2 = FVector(625.0f, 0.0f, 0.0f);
	Spline->AddSplinePoint(SplinePoint2, ESplineCoordinateSpace::Local, false);
	Spline->SetTangentAtSplinePoint(1, FVector::ZeroVector, ESplineCoordinateSpace::Local, false);
	Spline->SetSplinePointType(1, ESplinePointType::Linear);

	Spline->UpdateSpline();

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(DefaultSceneRoot);
	Camera->SetRelativeLocation(FVector(0.0f, 3720.0f, 1000.0f));
	Camera->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	Camera->SetFieldOfView(25.f);
	Camera->SetAspectRatio(0.55f);
	Camera->SetConstraintAspectRatio(true);
}

/*
 * Lifecycle Methods
 */
void APaddle::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<URobzanoidGameInstance>(GetGameInstance());
	check(GameInstance);

	CreateMovePaddleTimeline();
	ResetPaddle();
}

void APaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MovePaddleTimeline)
	{
		MovePaddleTimeline->TickComponent(DeltaTime, LEVELTICK_TimeOnly, nullptr);
	}
}

/*
 * Public Methods
 */
void APaddle::SpawnBall()
{
	if (Ball)
	{
		PaddleState = EPaddleState::Active;

		const FTransform SpawnTransform = LaunchPosition->GetComponentTransform();

		FActorSpawnParameters ActorSpawnParameters;
		ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		ActorSpawnParameters.TransformScaleMethod = ESpawnActorScaleMethod::MultiplyWithRoot;

		ABall* NewBall = Cast<ABall>(GetWorld()->SpawnActor(Ball, &SpawnTransform, ActorSpawnParameters));

		if (NewBall)
		{
			NewBall->OnDestroyed.AddDynamic(this, &APaddle::OnBallDestroyed);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("APaddle::SpawnBall() - Ball is null.  Please check that the asset has been assigned within Class Defaults."))
	}
}

void APaddle::LaunchBall()
{
	// Note:
	// Ball will be spawned, if there are any lives left, after being destroyed
	// LaunchBall() will set the speed/enable movement of the ProjectileMovementComponent.
}

void APaddle::MoveHorizontally(const float AxisValue)
{
	if (AxisValue > 0.0f)
	{
		MoveRight(AxisValue);
	}
	else if (AxisValue < 0.0f)
	{
		MoveLeft(AxisValue);
	}
	else
	{
		StopMoving();
	}
}


/*
 * Private Methods
 */
void APaddle::MoveRight(const float AxisValue)
{
	if (GameInstance)
	{
		const float Velocity = AxisValue * GameInstance->GetPaddleSpeedMultiplier();
		SetTimelinePlayRate(MovePaddleTimeline, Velocity);
		PlayTimeline(MovePaddleTimeline);		
	}
}

void APaddle::MoveLeft(const float AxisValue)
{
	if (GameInstance)
	{
		const float Velocity = (AxisValue * GameInstance->GetPaddleSpeedMultiplier()) * -1.0f;
		SetTimelinePlayRate(MovePaddleTimeline, Velocity);
		ReverseTimeline(MovePaddleTimeline);		
	}
}

void APaddle::StopMoving()
{
	StopTimeline(MovePaddleTimeline);
}

void APaddle::ResetPaddle()
{
	SetNewTimelineTime(MovePaddleTimeline, 0.5f);
}

void APaddle::MovePaddle(const float Value) const
{
	if (PaddleAnchor && Spline)
	{
		const float Distance = Spline->GetSplineLength() * Value;
		FTransform TransformAtDistanceAlongSpline = Spline->GetTransformAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
		TransformAtDistanceAlongSpline.SetScale3D(FVector::OneVector);

		PaddleAnchor->SetWorldTransform(TransformAtDistanceAlongSpline);
	}
}

void APaddle::OnBallDestroyed(AActor* DestroyedActor)
{
	if (PaddleState == EPaddleState::Active)
	{
		bool bWasExecuted = OnBallDestroyedDelegate.ExecuteIfBound();

		PaddleState = EPaddleState::Setup;
	}
}

void APaddle::CreateMovePaddleTimeline()
{
	if (MovePaddleCurve)
	{
		FOnTimelineFloat OnMovePaddleTimelineUpdate;
		FOnTimelineEventStatic OnMovePaddleTimelineFinished;

		MovePaddleTimeline = NewObject<UTimelineComponent>(this, FName("TimelineAnimation"));
		MovePaddleTimeline->CreationMethod = EComponentCreationMethod::UserConstructionScript;
		this->BlueprintCreatedComponents.Add(MovePaddleTimeline);
		MovePaddleTimeline->SetNetAddressable();

		MovePaddleTimeline->SetLooping(false);
		MovePaddleTimeline->SetTimelineLength(1.0f);
		MovePaddleTimeline->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);

		MovePaddleTimeline->SetPlaybackPosition(0.0f, false);

		OnMovePaddleTimelineUpdate.BindUFunction(this, FName{ TEXT("MovePaddleTimelineUpdate") });
		OnMovePaddleTimelineFinished.BindUFunction(this, FName{ TEXT("MovePaddleTimelineFinished") });

		MovePaddleTimeline->AddInterpFloat(MovePaddleCurve.Get(), OnMovePaddleTimelineUpdate);
		MovePaddleTimeline->SetTimelineFinishedFunc(OnMovePaddleTimelineFinished);

		MovePaddleTimeline->RegisterComponent();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("APaddle::CreateMovePaddleTimeline() - MovePaddleCurve is null.  Please check that the asset has been assigned within Class Defaults."));
	}
}

void APaddle::MovePaddleTimelineUpdate(float Value)
{
	MovePaddle(Value);
}

void APaddle::MovePaddleTimelineFinished()
{
	// Note: Deliberately left empty
}

/*
 * Utility Methods
 */
void APaddle::PlayTimeline(UTimelineComponent* Timeline)
{
	if (Timeline)
	{
		Timeline->Play();
	}
}

void APaddle::PlayTimelineFromStart(UTimelineComponent* Timeline)
{
	if (Timeline)
	{
		Timeline->PlayFromStart();
	}
}

void APaddle::StopTimeline(UTimelineComponent* Timeline)
{
	if (Timeline)
	{
		Timeline->Stop();
	}
}

void APaddle::ReverseTimeline(UTimelineComponent* Timeline)
{
	if (Timeline)
	{
		Timeline->Reverse();
	}
}

void APaddle::ReverseTimelineFromEnd(UTimelineComponent* Timeline)
{
	if (Timeline)
	{
		Timeline->ReverseFromEnd();
	}
}

void APaddle::SetNewTimelineTime(UTimelineComponent* Timeline, const float NewTime)
{
	if (Timeline)
	{
		Timeline->SetNewTime(NewTime);
	}
}

void APaddle::SetTimelinePlayRate(UTimelineComponent* Timeline, const float Rate)
{
	if (Timeline)
	{
		Timeline->SetPlayRate(Rate);
	}
}
