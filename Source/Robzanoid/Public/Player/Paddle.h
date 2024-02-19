// Copyright (c) 2024, Rob Meade. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Pawn.h"

#include "CommonTypes/CommonTypes.h"
#include "Delegates/BallDelegates.h"

#include "Paddle.generated.h"


// Forward Declarations
class UCameraComponent;
class UCapsuleComponent;
class USceneComponent;
class USplineComponent;
class UStaticMeshComponent;
class UTimelineComponent;

class ABall;
class URobzanoidGameInstance;


UCLASS()
class ROBZANOID_API APaddle : public APawn
{
	GENERATED_BODY()


public:

	APaddle();

	void SpawnBall();
	void LaunchBall();
	void MoveHorizontally(const float AxisValue);

	FOnBallDestroyedSignature OnBallDestroyedDelegate;

	EPaddleLaunchState GetPaddleState() const { return PaddleState; }


protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = "Robzanoid|Components")
	TObjectPtr<USceneComponent> DefaultSceneRoot = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Robzanoid|Components")
	TObjectPtr<USceneComponent> PaddleAnchor = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Robzanoid|Components")
	TObjectPtr<UStaticMeshComponent> StaticMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Robzanoid|Components")
	TObjectPtr<UCapsuleComponent> Capsule = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Robzanoid|Components")
	TObjectPtr<USceneComponent> LaunchPosition = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Robzanoid|Components")
	TObjectPtr<USplineComponent> Spline = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Robzanoid|Components")
	TObjectPtr<UCameraComponent> Camera = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Robzanoid|Components")
	TObjectPtr<UTimelineComponent> MovePaddleTimeline = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Robzanoid|Movement Properties")
	TObjectPtr<UCurveFloat> MovePaddleCurve = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Robzanoid|Ball Properties")
	TSubclassOf<ABall> BallClass = nullptr;


private:

	void MoveRight(const float AxisValue);
	void MoveLeft(const float AxisValue);
	void StopMoving();

	void ResetPaddle();
	void MovePaddle(const float Value) const;

	UFUNCTION()
	void OnBallDestroyed(AActor* DestroyedActor);

	void CreateMovePaddleTimeline();

	UFUNCTION()
	void MovePaddleTimelineUpdate(float Value);

	UFUNCTION()
	void MovePaddleTimelineFinished();

	/*
	 * Utility Methods
	 */
	void PlayTimeline(UTimelineComponent* Timeline);
	void PlayTimelineFromStart(UTimelineComponent* Timeline);
	void StopTimeline(UTimelineComponent* Timeline);
	void ReverseTimeline(UTimelineComponent* Timeline);
	void ReverseTimelineFromEnd(UTimelineComponent* Timeline);
	void SetNewTimelineTime(UTimelineComponent* Timeline, const float NewTime = 0.0f);
	void SetTimelinePlayRate(UTimelineComponent* Timeline, const float Rate = 1.0f);

	EPaddleLaunchState PaddleState = EPaddleLaunchState::PreparingToLaunch;

	UPROPERTY()
	TObjectPtr<URobzanoidGameInstance> GameInstance = nullptr;

	UPROPERTY()
	TObjectPtr<ABall> Ball = nullptr;
};
