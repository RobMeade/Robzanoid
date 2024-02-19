// Copyright (c) 2024, Rob Meade. All rights reserved.

#pragma once

#include "CommonTypes.generated.h"


// Enums
UENUM(BlueprintType)
enum class EGameplayState : uint8
{
	Initializing UMETA(DisplayName = "Initializing"),
	PlayInProgress UMETA(DisplayName = "Play In Progress"),
	LevelComplete UMETA(DisplayName = "Level Complete"),
	GameOver UMETA(DisplayName = "GameOver")
};

UENUM(BlueprintType)
enum class EBrickType : uint8
{
	DestructibleSingleHit UMETA(DisplayName = "Desctructible - Single Hit"),
	DestructibleMultiHit UMETA(DisplayName = "Destructible - Multi Hit"),
	Indestructible UMETA(DisplayName = "Indestructible")
};

UENUM(BlueprintType)
enum class EPaddleLaunchState : uint8
{
	PreparingToLaunch UMETA(DisplayName = "Preparing To Launch"),
	ReadyToLaunch UMETA(DisplayName = "Ready To Launch"),
	Launched UMETA(DisplayName = "Launched")
};


// Structs
USTRUCT(BlueprintType)
struct ROBZANOID_API FPlayerStateData
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Lives = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Score = 0;
};
