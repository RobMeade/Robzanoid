// Copyright (c) 2024, Rob Meade. All rights reserved.

#include "UI/MainMenuWidget.h"

#include "Components/Button.h"


/*
 * Constructor
 */
void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (OnePlayerGameButton)
	{
		OnePlayerGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnOnePlayerGameButtonClicked);
	}

	if (QuitGameButton)
	{
		QuitGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnQuitGameButtonClicked);
	}
}


/*
 * Private Methods
 */
void UMainMenuWidget::OnOnePlayerGameButtonClicked()
{
	bool bExecuted = OnOnePlayerGameButtonClickedDelegate.ExecuteIfBound();
}

void UMainMenuWidget::OnQuitGameButtonClicked()
{
	bool bExecuted = OnQuitGameButtonClickedDelegate.ExecuteIfBound();
}
