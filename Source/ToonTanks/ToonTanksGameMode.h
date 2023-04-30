// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(AActor* Actor);

	UFUNCTION(BlueprintCallable)
	void HandleGameStart();
	UPROPERTY(BlueprintReadOnly)
	int32 TargetTowers = 0;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool WonGame);

private:
	class ATank* Tank;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = true))
	class AToonTanksPlayerController* ToonTanksPlayerController;

	float StartDelay = 4.f;

	

	int32 GetTargetTowersCount() const;

	void BackToMenu() const;

	UPROPERTY(EditAnywhere, Category="UI")
	FName LevelName;
};
