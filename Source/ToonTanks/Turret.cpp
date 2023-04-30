// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"

#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATurret::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ATurret::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATurret::CheckFireCondition, FireRate, true);
}

void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Tank != nullptr) LookAtToTank();
}

void ATurret::LookAtToTank()
{
	//TODO - Check to see if the Tank is in range
	//TODO - If in range, rotate turret toward Tank
	if (TargetIntoTheRange()) RotateTurret(Tank->GetActorLocation());
}

bool ATurret::TargetIntoTheRange() const
{
	const float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
	return Distance <= FireRange;
}

void ATurret::CheckFireCondition()
{
	if(Tank->IsDead) return;
	if (TargetIntoTheRange())
	{
		Fire();
	}
}
