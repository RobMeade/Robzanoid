// Copyright (c) 2024, Rob Meade. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "GameOverlayWidget.generated.h"


// Forward Declarations
class UTextBlock;


UCLASS()
class ROBZANOID_API UGameOverlayWidget : public UUserWidget
{
	GENERATED_BODY()


public:

	void SetPlayerScore(const int32 Score) const;
	void SetPlayerLives(const int32 Lives) const;


private:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> PlayerScore;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> PlayerLives;

};
