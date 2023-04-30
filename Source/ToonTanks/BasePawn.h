// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	void HandleDestruction();

protected:
	UFUNCTION()
	void RotateTurret(FVector LookAtTarget) const;
	UFUNCTION()
	void Fire();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Base Components", meta = (AllowPrivateAccess = true))
	class UCapsuleComponent* CapsuleComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Base Components", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Base Components", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Base Components", meta = (AllowPrivateAccess = true))
	USceneComponent* ProjectilesSpawnPoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Variables", meta=(AllowPrivateAccess=true))
	float InterpolateSpeed = 15.f;
	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TSubclassOf<class AProjectile> ProjectileClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Base Components", meta=(AllowPrivateAccess = true))
	class UHealthComponent* HealthComponent;
	UPROPERTY(EditAnywhere, Category="Effects")
	UParticleSystem* DeathParticle;
	UPROPERTY(EditAnywhere, Category="Effects")
	USoundBase* DeathSound;
	UPROPERTY(EditAnywhere, Category="Effects")
	TSubclassOf<UCameraShakeBase> DeathCameraShake;
};
