// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"

#include "Tank.h"
#include "ToonTanksPlayerController.h"
#include "Turret.h"
#include "Kismet/GameplayStatics.h"

void AToonTanksGameMode::ActorDied(AActor* Actor)
{
	bool BackMenu = false;
	if (Actor == Tank)
	{
		Tank->HandleDestruction();
		if (ToonTanksPlayerController != nullptr)
		{
			ToonTanksPlayerController->SetPlayerEnabledState(false);
		}
		GameOver(false);
		BackMenu = true;
	}
	else if (ATurret* DestroyedTower = Cast<ATurret>(Actor))
	{
		DestroyedTower->HandleDestruction();
		--TargetTowers;
		if(TargetTowers <= 0)
		{
			GameOver(true);
			BackMenu = true;
		}
	}

	if(!BackMenu) return;
	FTimerHandle BackToMenuHandle;
	const FTimerDelegate TimerDel = FTimerDelegate::CreateUObject(this, &AToonTanksGameMode::BackToMenu);
	GetWorldTimerManager().SetTimer(BackToMenuHandle,TimerDel, 5.f, false);
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

int32 AToonTanksGameMode::GetTargetTowersCount() const
{
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATurret::StaticClass(), Towers);
	return Towers.Num();
}

void AToonTanksGameMode::BackToMenu() const
{
	UGameplayStatics::OpenLevel(GetWorld(),LevelName);
}

void AToonTanksGameMode::HandleGameStart()
{
	TargetTowers = GetTargetTowersCount();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();
	
	if (ToonTanksPlayerController)
	{
		ToonTanksPlayerController->SetPlayerEnabledState(false);
	}

	FTimerHandle PlayerEnableTimerHandle;
	const FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController,
	                                                                   &AToonTanksPlayerController::SetPlayerEnabledState,
	                                                                   true);
	GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, TimerDelegate, StartDelay, false);
}
