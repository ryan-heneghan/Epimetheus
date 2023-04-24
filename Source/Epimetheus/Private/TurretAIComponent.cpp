// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretAIComponent.h"

#include <concrt.h>

#include "GameFramework/Actor.h"

#include "Datasmith/DatasmithCore/Public/DatasmithDefinitions.h"

// Sets default values for this component's properties
UTurretAIComponent::UTurretAIComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	DistanceForClose = 700.f;
	CheckTime = 0.01f;
	FireRate = 1.5f;
	RotationSpeed = 5.f;

	Turret = GetOwner();
}


// Called when the game starts
void UTurretAIComponent::BeginPlay()
{
	Super::BeginPlay();

	// Initialise turret variables
	
	// Start Script
}


// Called every frame
void UTurretAIComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	CurrentDeltaTime = DeltaTime;

	if (CurrentCheckTime >= 0.f)
	{
		CurrentCheckTime -= DeltaTime;
	}
	else
	{
		CheckDistance();
	}

	if (IsPlayerClose)
	{
		if (CurrentFireTime >= 0.f)
		{
			CurrentFireTime -= DeltaTime;
		}
		else
		{
			TurretShoot();
		}
	}
}

void UTurretAIComponent::CheckDistance()
{
	// Get distance between turret and player
	TurretPosition = Turret->GetActorLocation();
	DistanceVector = TurretPosition - Player->GetActorLocation();
	DistanceFromPlayer = DistanceVector.Distance(TurretPosition, Player->GetActorLocation());

	if (DistanceFromPlayer <= DistanceForClose)
	{
		IsPlayerClose = true;
		LookAtPlayer();
	}
	else
	{
		IsPlayerClose = false;
	}

	// Reset Check timer
	CurrentCheckTime = CheckTime;
}

void UTurretAIComponent::LookAtPlayer()
{
	// Prevents turret from looking at player
	if (!IsPlayerClose)
		return;

	// Get and set rotation
	FVector Direction = TurretPosition - Player->GetActorLocation();
	FRotator Rot = FRotationMatrix::MakeFromX(Direction).Rotator();
	FRotator TargetRotation = FRotator(-Rot.Pitch, -Rot.Yaw, 0.f);
	FRotator MovingRotation =  FMath::RInterpTo(TurretHead->GetComponentRotation(), TargetRotation, CurrentDeltaTime, RotationSpeed);

	TurretHead->SetWorldRotation(MovingRotation);
}

void UTurretAIComponent::TurretShoot()
{
	// Get fire point location and rotation
	SpawnTransform = FTransform(TurretHead->GetComponentRotation(), TurretPosition + FirePositionOffset);
	
	// Spawn projectile
	SpawnBulletActor = GetWorld()->SpawnActor(TurretProjectile, &SpawnTransform);

	// Reset Timer
	CurrentFireTime = FireRate;
}

