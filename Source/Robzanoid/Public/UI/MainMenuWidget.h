// Copyright (c) 2024, Rob Meade. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Delegates/UIDelegates.h"

#include "MainMenuWidget.generated.h"


// Forward Declarations
class UButton;


UCLASS()
class ROBZANOID_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:

	FOnOnePlayerGameButtonClickedSignature OnOnePlayerGameButtonClickedDelegate;
	FOnQuitGameButtonClickedSignature OnQuitGameButtonClickedDelegate;


protected:

	virtual void NativeConstruct() override;


private:

	UFUNCTION()
	void OnOnePlayerGameButtonClicked();

	UFUNCTION()
	void OnQuitGameButtonClicked();

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> OnePlayerGameButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> QuitGameButton = nullptr;

};
