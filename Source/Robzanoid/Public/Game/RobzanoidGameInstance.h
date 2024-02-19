// Copyright (c) 2024, Rob Meade. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "CommonTypes/CommonTypes.h"

#include "RobzanoidGameInstance.generated.h"


// Forward Declarations
class ARobzanoidPlayerState;


UCLASS()
class ROBZANOID_API URobzanoidGameInstance : public UGameInstance
{
	GENERATED_BODY()


public:

	URobzanoidGameInstance();

	int32 GetDefaultPlayerLives() const { return DefaultPlayerLives; }
	float GetDefaultBallSpeed() const { return DefaultBallSpeed; }
	float GetPaddleSpeedMultiplier() const { return PaddleSpeedMultiplier; }
	int32 GetMultiHitBrickStrengthIncreaseLevelInterval() const { return IncreaseMultiHitBrickStrengthLevelInterval; }
	EGameplayState GetCurrentGameplayState() const { return CurrentGameplayState; }
	int32 GetCurrentLevelIndex() const { return CurrentLevelIndex; }
	FPlayerStateData GetPersistentData() const { return PersistentPlayerStateData; };
	void SetPersistentData(const FPlayerStateData& Data) { PersistentPlayerStateData = Data; };

	void MainMenu();
	void StartOnePlayerGame();
	void PlayInProgress();
	void LevelComplete(const FPlayerStateData& Data);
	void GameOver(const FPlayerStateData& Data);
	void QuitGame();


protected:

	UPROPERTY(EditDefaultsOnly, Category = "Robzanoid|Game Properties")
	TArray<TSoftObjectPtr<UWorld>> Levels;


private:

	bool HasMoreLevels() const;
	void LoadNextLevel();
	void LoadLevelByIndex(const int32 LevelIndex) const;

	UPROPERTY()
	FPlayerStateData PersistentPlayerStateData;

	EGameplayState CurrentGameplayState = EGameplayState::Initializing;
	int32 CurrentLevelIndex = 0;

	// Configuration Variables
	UPROPERTY(EditDefaultsOnly, Category = "Robzanoid|Game Configuration")
	int32 DefaultPlayerLives = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Robzanoid|Game Configuration")
	float DefaultBallSpeed = 1500.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Robzanoid|Game Configuration");
	float PaddleSpeedMultiplier = 2.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Robzanoid|Game Configuration")
	int32 IncreaseMultiHitBrickStrengthLevelInterval = 8;

};
