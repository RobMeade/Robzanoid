// Copyright (c) 2024, Rob Meade. All rights reserved.

#include "UI/RobzanoidHUD.h"

#include "Blueprint/UserWidget.h"

#include "UI/GameOverlayWidget.h"
#include "UI/GameOverWidget.h"
#include "UI/MainMenuWidget.h"


/*
 * Public Methods
 */
void ARobzanoidHUD::CreateMainMenuWidget()
{
	APlayerController* PlayerController = GetOwningPlayerController();

	if (PlayerController && MainMenuWidgetClass)
	{
		MainMenuWidget = CreateWidget<UMainMenuWidget>(PlayerController, MainMenuWidgetClass);
		MainMenuWidget->AddToViewport();

		MainMenuWidget->OnOnePlayerGameButtonClickedDelegate.BindDynamic(this, &ARobzanoidHUD::OnOnePlayerGameButtonClicked);
		MainMenuWidget->OnQuitGameButtonClickedDelegate.BindDynamic(this, &ARobzanoidHUD::OnQuitGameButtonClicked);
	}
}

void ARobzanoidHUD::CreateGameOverWidget(const int32& Score)
{
	APlayerController* PlayerController = GetOwningPlayerController();

	if (PlayerController && GameOverWidgetClass)
	{
		GameOverWidget = CreateWidget<UGameOverWidget>(PlayerController, GameOverWidgetClass);
		GameOverWidget->SetPlayerScore(Score);
		GameOverWidget->AddToViewport();

		GameOverWidget->OnMainMenuButtonClickedDelegate.BindDynamic(this, &ARobzanoidHUD::OnMainMenuButtonClicked);
	}
}

void ARobzanoidHUD::CreateGameOverlayWidget()
{
	APlayerController* PlayerController = GetOwningPlayerController();

	if (PlayerController && GameOverlayWidgetClass)
	{
		GameOverlayWidget = CreateWidget<UGameOverlayWidget>(PlayerController, GameOverlayWidgetClass);
		GameOverlayWidget->AddToViewport();
	}
}

void ARobzanoidHUD::SetPlayerScore(const int32& Score) const
{
	if (GameOverlayWidget)
	{
		GameOverlayWidget->SetPlayerScore(Score);
	}
}

void ARobzanoidHUD::SetPlayerLives(const int32& Lives) const
{
	if (GameOverlayWidget)
	{
		GameOverlayWidget->SetPlayerLives(Lives);
	}
}


/*
 * Private Methods
 */
void ARobzanoidHUD::OnOnePlayerGameButtonClicked()
{
	bool bExecuted = OnOnePlayerGameButtonClickedDelegate.ExecuteIfBound();
}

void ARobzanoidHUD::OnQuitGameButtonClicked()
{
	bool bExecuted = OnQuitGameButtonClickedDelegate.ExecuteIfBound();
}

void ARobzanoidHUD::OnMainMenuButtonClicked()
{
	bool bExecuted = OnMainMenuButtonClickedDelegate.ExecuteIfBound();
}
