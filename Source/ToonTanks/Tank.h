// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

	ATank();

public:
	void HandleDestruction();

	APlayerController* GetTankPlayerController() const { return TankPlayerController; }
	bool IsDead = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Variables")
	bool Reloading = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Variables")
	float ReloadingTime = .5f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess=true))
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess=true))
	UCameraComponent* CameraComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Variables", meta=(AllowPrivateAccess=true))
	float Speed = 400;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Variables", meta=(AllowPrivateAccess=true))
	float TurnRate = 45.f;
	UPROPERTY(VisibleAnywhere, Category="References")
	APlayerController* TankPlayerController;

	UFUNCTION()
	void Move(float Value);
	UFUNCTION()
	void Turn(float Value);
	UFUNCTION()
	void RotateTurretTank() const;
	UFUNCTION()
	void ValidateFire();
	UFUNCTION()
	void Reloaded();

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
