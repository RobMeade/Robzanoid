// Copyright (c) 2024, Rob Meade. All rights reserved.


#include "Game/RobzanoidSinglePlayerGameMode.h"

#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

#include "CommonTypes/CommonTypes.h"
#include "Environment/Brick/BrickBase.h"
#include "Game/RobzanoidGameInstance.h"
#include "Player/RobzanoidPlayerController.h"
#include "Player/RobzanoidPlayerState.h"


/*
 * Constructor
 */
ARobzanoidSinglePlayerGameMode::ARobzanoidSinglePlayerGameMode() : ARobzanoidGameModeBase()
{
	
}


/*
 * Lifecycle Methods
 */
void ARobzanoidSinglePlayerGameMode::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<URobzanoidGameInstance>(GetGameInstance());
	PlayerController = Cast<ARobzanoidPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	CurrentPlayerState = PlayerController->GetPlayerState<ARobzanoidPlayerState>();
	check(GameInstance);
	check(PlayerController);
	check(CurrentPlayerState);

    InitializeBricks();
	InitializePlayerState();

	PlayerController->OnBallDestroyedDelegate.BindDynamic(this, &ARobzanoidSinglePlayerGameMode::OnBallDestroyed);

	GameInstance->PlayInProgress();
}


/*
 * Private Methods
 */
void ARobzanoidSinglePlayerGameMode::InitializeBricks()
{
	if (GameInstance)
	{
		for (TActorIterator<AActor> ActorItr(GetWorld(), ABrickBase::StaticClass()); ActorItr; ++ActorItr)
		{
			if (ABrickBase* Brick = Cast<ABrickBase>(*ActorItr))
			{
				// Count only destructible bricks
				if (Brick->GetBrickType() != EBrickType::Indestructible)
				{
					BricksRemaining++;

					Brick->OnDestroyed.AddDynamic(this, &ARobzanoidSinglePlayerGameMode::OnBrickDestroyed);

					// Set multi hit brick strength based on current level number
					if (Brick->GetBrickType() == EBrickType::DestructibleMultiHit)
					{
						const int32 BrickStrength = Brick->GetStrength() + (GameInstance->GetCurrentLevelIndex() / GameInstance->GetMultiHitBrickStrengthIncreaseLevelInterval());
						Brick->SetStrength(BrickStrength);
					}
				}
			}
		}		
	}
}

void ARobzanoidSinglePlayerGameMode::InitializePlayerState() const
{
	if (GameInstance && CurrentPlayerState)
	{
		// Note: Determine whether we are on the first level, or, a subsequently level
		if (GameInstance->GetCurrentLevelIndex() == 1)
		{
			CurrentPlayerState->Initialize(GameInstance->GetDefaultPlayerLives(), 0);
		}
		else if (GameInstance->GetCurrentLevelIndex() > 1)
		{
			const auto& [Lives, Score] = GameInstance->GetPersistentData();
			CurrentPlayerState->Initialize(Lives, Score);
		}
	}
}

void ARobzanoidSinglePlayerGameMode::OnBrickDestroyed(AActor* DestroyedActor)
{
	if (const ABrickBase* Brick = Cast<ABrickBase>(DestroyedActor))
	{
		if (PlayerController && CurrentPlayerState)
		{
			CurrentPlayerState->IncrementScore(Brick->GetPoints());
			PlayerController->UpdateHUDScore(CurrentPlayerState->GetCurrentScore());

			BricksRemaining--;

			if (BricksRemaining <= 0)
			{
				GameInstance->LevelComplete(CurrentPlayerState->GetPlayerStateData());
			}
		}		
	}
}

void ARobzanoidSinglePlayerGameMode::OnBallDestroyed()
{
	if (GameInstance && PlayerController && CurrentPlayerState)
	{
		CurrentPlayerState->DecrementLives();
		PlayerController->UpdateHUDLives(CurrentPlayerState->GetCurrentLives());

		if (CurrentPlayerState->GetCurrentLives() <= 0)
		{
			GameInstance->GameOver(CurrentPlayerState->GetPlayerStateData());
		}
	}
}
