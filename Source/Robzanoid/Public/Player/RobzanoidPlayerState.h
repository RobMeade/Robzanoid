// Copyright (c) 2024, Rob Meade. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"

#include "RobzanoidPlayerState.generated.h"


// Forward Declarations
struct FPlayerStateData;


UCLASS()
class ROBZANOID_API ARobzanoidPlayerState : public APlayerState
{
	GENERATED_BODY()


public:

	void Initialize(const int32 NewLives, const int32 NewScore);
	void IncrementLives();
	void DecrementLives();
	void IncrementScore(const int32 Points);

	int32 GetCurrentLives() const { return CurrentLives; }
	int32 GetCurrentScore() const { return CurrentScore; }

	FPlayerStateData GetPlayerStateData() const;


private:

	UPROPERTY()
	int32 CurrentLives = 0;

	UPROPERTY()
	int32 CurrentScore = 0;

};
