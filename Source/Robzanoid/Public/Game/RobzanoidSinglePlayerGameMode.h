// Copyright (c) 2024, Rob Meade. All rights reserved.

#pragma once

#include "CoreMinimal.h"

#include "Game/RobzanoidGameModeBase.h"

#include "RobzanoidSinglePlayerGameMode.generated.h"


// Forward Declarations
class ARobzanoidPlayerController;
class ARobzanoidPlayerState;
class URobzanoidGameInstance;


UCLASS()
class ROBZANOID_API ARobzanoidSinglePlayerGameMode : public ARobzanoidGameModeBase
{
	GENERATED_BODY()


public:

	ARobzanoidSinglePlayerGameMode();


protected:

	virtual void BeginPlay() override;


private:

	void InitializeBricks();
	void InitializePlayerState() const;

	UFUNCTION()
	void OnBrickDestroyed(AActor* DestroyedActor);

	UFUNCTION()
	void OnBallDestroyed();

	UPROPERTY()
	TObjectPtr<URobzanoidGameInstance> GameInstance = nullptr;

	UPROPERTY()
	TObjectPtr<ARobzanoidPlayerController> PlayerController = nullptr;

	UPROPERTY()
	TObjectPtr<ARobzanoidPlayerState> CurrentPlayerState = nullptr;

	int32 BricksRemaining = 0;

};
