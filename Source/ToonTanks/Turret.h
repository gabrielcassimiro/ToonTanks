// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Turret.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATurret : public ABasePawn
{
	GENERATED_BODY()

public:
	void HandleDestruction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LookAtToTank();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Tank", meta=(AllowPrivateAccess=true))
	class ATank* Tank;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Turret")
	float FireRange = 500.f;

	FTimerHandle FireRateTimerHandle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Turret")
	float FireRate = 2;

	bool TargetIntoTheRange() const;

	void CheckFireCondition();
};
