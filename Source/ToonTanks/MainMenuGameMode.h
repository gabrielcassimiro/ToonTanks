// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void StartGame();
	UFUNCTION(BlueprintCallable)
	void QuitGame();
	UPROPERTY(EditAnywhere, Category="Levels")
	FName LevelName;

protected:
	virtual void BeginPlay() override;
};
