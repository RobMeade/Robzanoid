// Copyright (c) 2024, Rob Meade. All rights reserved.


#include "UI/GameOverlayWidget.h"

#include "Components/TextBlock.h"


/*
 * Public Methods
 */
void UGameOverlayWidget::SetPlayerScore(const int32 Score) const
{
	if (PlayerScore)
	{
		PlayerScore->SetText(FText::FromString(FString::FromInt(Score)));
	}
}

void UGameOverlayWidget::SetPlayerLives(const int32 Lives) const
{
	if (PlayerLives)
	{
		PlayerLives->SetText(FText::FromString(FString::FromInt(Lives)));
	}
}
