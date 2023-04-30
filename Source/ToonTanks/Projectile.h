// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess=true))
	UStaticMeshComponent* ProjectileMesh;
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovementComponent;
	UPROPERTY(EditAnywhere, Category="Components")
	float ProjectileSpeed = 1500.f;
	UPROPERTY(EditAnywhere)
	float Damage = 50.f;
	UPROPERTY(EditAnywhere, Category="Effects")
	UParticleSystem* ExplosionParticle;
	UPROPERTY(VisibleAnywhere, Category="Effects")
	UParticleSystemComponent* TrailParticles;
	UPROPERTY(EditAnywhere, Category="Effects")
	USoundBase* LaunchSound;
	UPROPERTY(EditAnywhere, Category="Effects")
	USoundBase* HitSound;
	UPROPERTY(EditAnywhere, Category="Effects")
	TSubclassOf<UCameraShakeBase> HitCameraShake;

	//Function to HitEvents
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	           FVector NormalImpulse, const FHitResult& Hit);
	
};
