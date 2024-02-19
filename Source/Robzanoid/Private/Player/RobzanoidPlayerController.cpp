// Copyright (c) 2024, Rob Meade. All rights reserved.

#include "Player/RobzanoidPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"

#include "CommonTypes/CommonTypes.h"
#include "Game/RobzanoidGameInstance.h"
#include "Game/RobzanoidSinglePlayerGameMode.h"
#include "Player/Paddle.h"
#include "Player/RobzanoidPlayerState.h"
#include "UI/RobzanoidHUD.h"


/*
 * Constructor
 */
ARobzanoidPlayerController::ARobzanoidPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}


/*
 * Lifecycle Methods
 */
void ARobzanoidPlayerController::BeginPlay()
{
	GameInstance = Cast<URobzanoidGameInstance>(GetGameInstance());
	check(GameInstance);

	HUD = Cast<ARobzanoidHUD>(GetHUD());
	check(HUD);

	if (GameInstance->GetCurrentLevelIndex() == 0)
	{
		if (GameInstance->GetCurrentGameplayState() == EGameplayState::Initializing)
		{
			DisplayMainMenu();			
		}
		else if (GameInstance->GetCurrentGameplayState() == EGameplayState::GameOver)
		{
			DisplayGameOver();
		}

		FInputModeUIOnly InputMode;
		SetInputMode(InputMode);
		bShowMouseCursor = true;
	}
	else
	{
		GameMode = Cast<ARobzanoidSinglePlayerGameMode>(UGameplayStatics::GetGameMode(this));

		AddInputMappingContext();
		DisplayHUD();

		FInputModeGameOnly InputMode;
		SetInputMode(InputMode);
		bShowMouseCursor = false;
	}
}

void ARobzanoidPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveHorizontallyAction, ETriggerEvent::Triggered, this, &ARobzanoidPlayerController::MoveHorizontally);
	EnhancedInputComponent->BindAction(MoveHorizontallyAction, ETriggerEvent::Completed, this, &ARobzanoidPlayerController::MoveHorizontally);
	EnhancedInputComponent->BindAction(LaunchBallAction, ETriggerEvent::Triggered, this, &ARobzanoidPlayerController::LaunchBall);
}

void ARobzanoidPlayerController::OnPossess(APawn* InPawn)
{
	Paddle = Cast<APaddle>(InPawn);

	if (Paddle)
	{
		SetViewTarget(Paddle);

		Paddle->SpawnBall();
		Paddle->OnBallDestroyedDelegate.BindDynamic(this, &ARobzanoidPlayerController::OnBallDestroyed);			
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AARobzanoidPlayerController::OnPosses - Unable to cast InPawn to APaddle.  Check Default Pawn has been set correctly in the GameMode."))
	}
}


/*
 * Public Methods
 */
void ARobzanoidPlayerController::UpdateHUDLives(const int32 Lives) const
{
	if (HUD)
	{
		HUD->SetPlayerLives(Lives);
	}
}

void ARobzanoidPlayerController::UpdateHUDScore(const int32 Score) const
{
	if (HUD)
	{
		HUD->SetPlayerScore(Score);
	}
}

void ARobzanoidPlayerController::SpawnBall() const
{
	if (GameInstance && Paddle)
	{
		if (GameInstance->GetCurrentGameplayState() != EGameplayState::GameOver && Paddle->GetPaddleState() == EPaddleLaunchState::PreparingToLaunch)
		{
			Paddle->SpawnBall();
		}
	}
}


/*
 * Private Methods
 */
void ARobzanoidPlayerController::AddInputMappingContext() const
{
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(RobzanoidDefaultContext, 0);
	}
}

void ARobzanoidPlayerController::DisplayMainMenu() const
{
	if (HUD)
	{
		HUD->CreateMainMenuWidget();

		HUD->OnOnePlayerGameButtonClickedDelegate.BindDynamic(this, &ARobzanoidPlayerController::OnOnePlayerGameButtonClicked);
		HUD->OnQuitGameButtonClickedDelegate.BindDynamic(this, &ARobzanoidPlayerController::OnQuitGameButtonClicked);
	}
}

void ARobzanoidPlayerController::DisplayGameOver() const
{
	if (GameInstance && HUD)
	{
		const auto& [Lives, Score] = GameInstance->GetPersistentData();

		HUD->CreateGameOverWidget(Score);

		HUD->OnMainMenuButtonClickedDelegate.BindDynamic(this, &ARobzanoidPlayerController::OnMainMenuButtonClicked);
	}
}

void ARobzanoidPlayerController::DisplayHUD() const
{
	const ARobzanoidPlayerState* CurrentPlayerState = GetPlayerState<ARobzanoidPlayerState>();

	if (CurrentPlayerState && HUD)
	{
		HUD->CreateGameOverlayWidget();

		HUD->SetPlayerScore(CurrentPlayerState->GetCurrentScore());
		HUD->SetPlayerLives(CurrentPlayerState->GetCurrentLives());
	}
}

void ARobzanoidPlayerController::MoveHorizontally(const FInputActionValue& InputActionValue)
{
	if (GameInstance && Paddle)
	{
		if (GameInstance->GetCurrentGameplayState() == EGameplayState::GameOver)
		{
			Paddle->MoveHorizontally(0.0f);
		}
		else
		{
			Paddle->MoveHorizontally(InputActionValue.Get<FVector2D>().X);
		}
	}
}

void ARobzanoidPlayerController::LaunchBall(const FInputActionValue& InputActionValue)
{
	if (GameInstance && Paddle)
	{
		if (GameInstance->GetCurrentGameplayState() != EGameplayState::GameOver && Paddle->GetPaddleState() == EPaddleLaunchState::ReadyToLaunch)
		{
			Paddle->LaunchBall();
		}
	}
}

void ARobzanoidPlayerController::OnOnePlayerGameButtonClicked()
{
	if (GameInstance)
	{
		GameInstance->StartOnePlayerGame();
	}
}

void ARobzanoidPlayerController::OnQuitGameButtonClicked()
{
	if (GameInstance)
	{
		GameInstance->QuitGame();
	}
}

void ARobzanoidPlayerController::OnMainMenuButtonClicked()
{
	if (GameInstance)
	{
		GameInstance->MainMenu();
	}
}

void ARobzanoidPlayerController::OnBallDestroyed()
{
	bool bWasExecuted = OnBallDestroyedDelegate.ExecuteIfBound();
}
