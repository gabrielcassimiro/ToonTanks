// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	if (ProjectileMovementComponent)
	{
		ProjectileMovementComponent->InitialSpeed = ProjectileSpeed;
		ProjectileMovementComponent->MaxSpeed = ProjectileSpeed;
	}

	TrailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Trail"));
	TrailParticles->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	if(LaunchSound != nullptr) UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
                        FVector NormalImpulse, const FHitResult& Hit)
{
	const auto MyOwner = GetOwner();
	if (MyOwner == nullptr) return;
	const auto MyOwnerInstigator = MyOwner->GetInstigatorController();
	const auto DamageTypeClass = UDamageType::StaticClass();

	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, DamageTypeClass);
		if(HitSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		}
		if (ExplosionParticle != nullptr)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionParticle, GetActorLocation(), GetActorRotation());
		}
		if(HitCameraShake != nullptr)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShake);
		}
		Destroy();
	}
}
