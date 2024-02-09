// Copyright (c) 2024, Rob Meade. All rights reserved.

#include "Game/RobzanoidGameInstance.h"

#include "Kismet/GameplayStatics.h"


/*
 * Constructor
 */
URobzanoidGameInstance::URobzanoidGameInstance()
{
	//check(Levels.Num() > 0);
	if (Levels.Num() <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("No levels have been configured within the Game Instance."));
	}
}


/*
 * Public Methods
 */
void URobzanoidGameInstance::MainMenu()
{
	// TODO: Potential saving on performance here if we DONT load the level again.
	//		 At this point, we are already on the Level Index 0, we just need to hide
	//		 the GameOver widget and display the MainMenu widget.
	CurrentGameplayState = EGameplayState::Initializing;
	CurrentLevelIndex = 0;

	LoadLevelByIndex(CurrentLevelIndex);
}

void URobzanoidGameInstance::StartOnePlayerGame()
{
	CurrentGameplayState = EGameplayState::Initializing;

	LoadNextLevel();
}

void URobzanoidGameInstance::PlayInProgress()
{
	CurrentGameplayState = EGameplayState::PlayInProgress;
}

void URobzanoidGameInstance::LevelComplete(const FPlayerStateData& Data)
{
	CurrentGameplayState = EGameplayState::LevelComplete;

	SetPersistentData(Data);
	LoadNextLevel();
}

void URobzanoidGameInstance::GameOver(const FPlayerStateData& Data)
{
	CurrentGameplayState = EGameplayState::GameOver;
	CurrentLevelIndex = 0;

	SetPersistentData(Data);
	LoadLevelByIndex(CurrentLevelIndex);
}

void URobzanoidGameInstance::QuitGame()
{
#if WITH_EDITOR
	if (!GetWorld()->IsPlayInEditor())
	{
		FGenericPlatformMisc::RequestExit(false);
	}
	else
	{
		if (GEditor)
		{
			GEditor->RequestEndPlayMap();
		}
	}
#else
	FGenericPlatformMisc::RequestExit(false);
#endif
}


/*
 * Private Methods
 */
bool URobzanoidGameInstance::HasMoreLevels() const
{
	return (CurrentLevelIndex + 1) < Levels.Num();
}

void URobzanoidGameInstance::LoadNextLevel()
{
	if (HasMoreLevels())
	{
		CurrentLevelIndex++;

		LoadLevelByIndex(CurrentLevelIndex);
	}
	else
	{
		GameOver(PersistentPlayerStateData);
	}
}

void URobzanoidGameInstance::LoadLevelByIndex(const int32 LevelIndex) const
{
	const TSoftObjectPtr<UWorld>& LevelToLoad = Levels[LevelIndex];
	if (!LevelToLoad.IsNull())
	{
		UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), LevelToLoad);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to load level with index: %d."), LevelIndex);
	}
}
