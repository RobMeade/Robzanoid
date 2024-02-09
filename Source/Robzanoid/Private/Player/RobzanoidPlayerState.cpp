// Copyright (c) 2024, Rob Meade. All rights reserved.

#include "Player/RobzanoidPlayerState.h"

#include "CommonTypes/CommonTypes.h"


/*
 * Public Methods
 */
void ARobzanoidPlayerState::Initialize(const int32 NewLives, const int32 NewScore)
{
	CurrentLives = NewLives;
	CurrentScore = NewScore;
}

void ARobzanoidPlayerState::IncrementLives()
{
	CurrentLives++;
}

void ARobzanoidPlayerState::DecrementLives()
{
	CurrentLives--;
}

void ARobzanoidPlayerState::IncrementScore(const int32 Points)
{
	CurrentScore += Points;
}

FPlayerStateData ARobzanoidPlayerState::GetPlayerStateData() const
{
	FPlayerStateData Data;
	Data.Lives = CurrentLives;
	Data.Score = CurrentScore;
	return Data;
}
