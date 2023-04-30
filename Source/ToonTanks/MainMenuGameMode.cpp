// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameMode.h"

#include "Kismet/GameplayStatics.h"

void AMainMenuGameMode::StartGame()
{
	UGameplayStatics::OpenLevel(GetWorld(), LevelName);
}

void AMainMenuGameMode::QuitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}

void AMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* Controller = GetWorld()->GetFirstPlayerController();

	Controller->DisableInput(Controller);
	Controller->bShowMouseCursor = true;
}
