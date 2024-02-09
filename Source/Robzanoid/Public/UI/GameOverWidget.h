// Copyright (c) 2024, Rob Meade. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Delegates/UIDelegates.h"

#include "GameOverWidget.generated.h"


// Forward Declarations
class UButton;
class UTextBlock;


UCLASS()
class ROBZANOID_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

	
public:

	FOnMainMenuButtonClickedSignature OnMainMenuButtonClickedDelegate;

	void SetPlayerScore(const int32& Score) const;


protected:

	virtual void NativeConstruct() override;


private:

	UFUNCTION()
	void OnMainMenuButtonClicked();

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> PlayerScore = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> MainMenuButton = nullptr;

};
