// Copyright (c) 2024, Rob Meade. All rights reserved.


#include "UI/GameOverWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"


/*
 * Constructor
 */
void UGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (MainMenuButton)
	{
		MainMenuButton->OnClicked.AddDynamic(this, &UGameOverWidget::OnMainMenuButtonClicked);
	}
}

/*
 * Public Methods
 */
void UGameOverWidget::SetPlayerScore(const int32& Score) const
{
	if (PlayerScore)
	{
		PlayerScore->SetText(FText::FromString(FString::FromInt(Score)));
	}
}


/*
 * Private Methods
 */
void UGameOverWidget::OnMainMenuButtonClicked()
{
	bool bExecuted = OnMainMenuButtonClickedDelegate.ExecuteIfBound();
}
