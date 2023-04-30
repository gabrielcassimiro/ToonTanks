// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

#include "HealthComponent.h"
#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePawn::ABasePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Construct Objects
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	//Set RootComponent
	RootComponent = CapsuleComponent;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComponent);
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);
	ProjectilesSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectiles Spawn Points"));
	ProjectilesSpawnPoint->SetupAttachment(TurretMesh);
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
}

void ABasePawn::HandleDestruction()
{
	if(DeathParticle != nullptr)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation(), GetActorRotation());
	}
	if(DeathSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	}
	if(DeathCameraShake != nullptr)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShake);
	}
}

void ABasePawn::RotateTurret(FVector LookAtTarget) const
{
	const FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	const FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
	TurretMesh->SetWorldRotation(FMath::RInterpTo(TurretMesh->GetComponentRotation(), LookAtRotation,
	                                              UGameplayStatics::GetWorldDeltaSeconds(this), InterpolateSpeed));
}

void ABasePawn::Fire()
{
	//TODO - Fire Bullet
	// DrawDebugSphere(GetWorld(), ProjectilesSpawnPoint->GetComponentLocation(), 20.f, 12, FColor::Green, false, 5.f);
	const FVector Location = ProjectilesSpawnPoint->GetComponentLocation();
	const FRotator Rotation = ProjectilesSpawnPoint->GetComponentRotation();
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);
	Projectile->SetOwner(this);
}
