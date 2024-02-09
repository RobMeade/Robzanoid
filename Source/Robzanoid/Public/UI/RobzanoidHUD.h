// Copyright (c) 2024, Rob Meade. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "Delegates/UIDelegates.h"

#include "RobzanoidHUD.generated.h"


// Forward Declarations
class UGameOverlayWidget;
class UGameOverWidget;
class UMainMenuWidget;


UCLASS()
class ROBZANOID_API ARobzanoidHUD : public AHUD
{
	GENERATED_BODY()


public:

	void CreateMainMenuWidget();
	void CreateGameOverWidget(const int32& Score);
	void CreateGameOverlayWidget();
	void SetPlayerScore(const int32& Score) const;
	void SetPlayerLives(const int32& Lives) const;

	FOnOnePlayerGameButtonClickedSignature OnOnePlayerGameButtonClickedDelegate;
	FOnQuitGameButtonClickedSignature OnQuitGameButtonClickedDelegate;
	FOnMainMenuButtonClickedSignature OnMainMenuButtonClickedDelegate;


protected:

	UPROPERTY(EditDefaultsOnly, Category = "Robzanoid|UI")
	TSubclassOf<UUserWidget> MainMenuWidgetClass;

	UPROPERTY()
	TObjectPtr<UMainMenuWidget> MainMenuWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Robzanoid|UI")
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	UPROPERTY()
	TObjectPtr<UGameOverWidget> GameOverWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Robzanoid|UI")
	TSubclassOf<UUserWidget> GameOverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UGameOverlayWidget> GameOverlayWidget;


private:

	UFUNCTION()
	void OnOnePlayerGameButtonClicked();

	UFUNCTION()
	void OnQuitGameButtonClicked();

	UFUNCTION()
	void OnMainMenuButtonClicked();

};
