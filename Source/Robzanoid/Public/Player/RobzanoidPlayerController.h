// Copyright (c) 2024, Rob Meade. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "Delegates/BallDelegates.h"

#include "RobzanoidPlayerController.generated.h"


// Forward Declarations
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

class APaddle;
class URobzanoidGameInstance;
class ARobzanoidHUD;
class ARobzanoidSinglePlayerGameMode;


UCLASS()
class ROBZANOID_API ARobzanoidPlayerController : public APlayerController
{
	GENERATED_BODY()


public:

	ARobzanoidPlayerController();

	FOnBallDestroyedSignature OnBallDestroyedDelegate;

	void UpdateHUDLives(const int32 Lives) const;
	void UpdateHUDScore(const int32 Score) const;


protected:

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;


private:

	void AddInputMappingContext() const;
	void DisplayMainMenu() const;
	void DisplayGameOver() const;
	void DisplayHUD() const;
	void MoveHorizontally(const FInputActionValue& InputActionValue);
	void LaunchBall(const FInputActionValue& InputActionValue);

	UFUNCTION()
	void OnOnePlayerGameButtonClicked();

	UFUNCTION()
	void OnQuitGameButtonClicked();

	UFUNCTION()
	void OnMainMenuButtonClicked();

	UFUNCTION()
	void OnBallDestroyed();

	UPROPERTY(EditDefaultsOnly, Category = "Robzanoid|Input")
	TObjectPtr<UInputMappingContext> RobzanoidDefaultContext = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Robzanoid|Input")
	TObjectPtr<UInputAction> MoveHorizontallyAction = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Robzanoid|Input")
	TObjectPtr<UInputAction> LaunchBallAction = nullptr;

	UPROPERTY()
	TObjectPtr<URobzanoidGameInstance> GameInstance = nullptr;

	UPROPERTY()
	TObjectPtr<ARobzanoidSinglePlayerGameMode> GameMode = nullptr;

	UPROPERTY()
	TObjectPtr<APaddle> Paddle = nullptr;

	UPROPERTY()
	TObjectPtr<ARobzanoidHUD> HUD;

};
