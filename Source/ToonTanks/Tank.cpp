// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	IsDead = true;
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	TankPlayerController = Cast<APlayerController>(GetController());
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotateTurretTank();
}


void ATank::Move(float Value)
{
	// if(GEngine)
	// {
	// 	const FString TextToShow = FString::Printf(TEXT("Move value: %f"),Value);
	// 	GEngine->AddOnScreenDebugMessage(-1, 0.5f,FColor::Blue, TextToShow);
	// }

	const float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

	FVector DeltaLocation = FVector::ZeroVector;
	DeltaLocation.X = Value * DeltaTime * Speed;
	AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value)
{
	//Rotate in Yaw(Z)
	const float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	FRotator DeltaRotation = FRotator::ZeroRotator;
	DeltaRotation.Yaw = Value * TurnRate * DeltaTime;
	AddActorLocalRotation(DeltaRotation);
}

void ATank::RotateTurretTank() const
{
	if(TankPlayerController)
	{
		FHitResult HitResult;
		TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
		//Persistent Line = false e LifeTime -1.f para que seja constante a todo frame do jogo
		// DrawDebugSphere(GetWorld(), HitResult.ImpactPoint,20.f, 12,FColor::Red,false, -1.f);
		RotateTurret(HitResult.ImpactPoint);
	}
}

void ATank::ValidateFire()
{
	if(!Reloading)
	{
		Fire();
		Reloading = true;
		FTimerHandle ReloadingTimerHandle;
		FTimerDelegate ReloadingTimerDelegate = FTimerDelegate::CreateUObject(this,&ATank::Reloaded);
		GetWorldTimerManager().SetTimer(ReloadingTimerHandle,ReloadingTimerDelegate, ReloadingTime, false);
	}
}

void ATank::Reloaded()
{
	Reloading = false;
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::ValidateFire);
}
