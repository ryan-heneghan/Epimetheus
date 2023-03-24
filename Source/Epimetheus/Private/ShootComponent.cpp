// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootComponent.h"

// Sets default values for this component's properties
UShootComponent::UShootComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

	m_PowerLevel = 1;
	m_CurrentBuildTimer = 0.f;
	m_CanStartBuilding = false;

	m_Level2PowerPoint = 0.5f;
	m_Level3PowerPoint = 1.5f;
}


// Called when the game starts
void UShootComponent::BeginPlay()
{
	Super::BeginPlay();

	m_CurrentBuildTimer = 0.f;
	
	if (m_CurrentBuildTimer >= m_MaxBuildTime)
	{
		ShootProjectile();
	}
}


// Called every frame
void UShootComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!m_CanStartBuilding)
	{
		return;
	}
	
	m_CurrentBuildTimer += DeltaTime;

	if (m_CurrentBuildTimer >= m_MaxBuildTime)
	{
		ShootProjectile();
	}
}

void UShootComponent::BuildProjectile()
{
	m_CurrentBuildTimer = 0.f;
	m_CanStartBuilding = true;
}


void UShootComponent::ShootProjectile()
{
	if (ArrowComponent == NULL)
	{
		return;
	}
	
	// Stop building power
	m_CanStartBuilding = false;

	// Get the world location of the arrow component
	FVector SpawnLocation = ArrowComponent->GetComponentToWorld().GetLocation();

	// Set the desired rotation for the spawned actor
	FRotator SpawnRotation = ArrowComponent->GetComponentRotation();

	// Create a new FTransform object using the spawn location and rotation
	FTransform SpawnTransform = FTransform(SpawnRotation, SpawnLocation);
	
	if (m_CurrentBuildTimer < m_Level2PowerPoint)
	{
		// Shoot Level 1 Projectile
		m_PowerLevel = 1;

		// Spawn an instance of the Blueprint class using the GetWorld()->SpawnActor function
		AActor* SpawnActor = GetWorld()->SpawnActor(m_Projectile1, &SpawnTransform);

		SpawnProjectileBP = m_Projectile1;
	}
	else if (m_CurrentBuildTimer >= m_Level2PowerPoint && m_CurrentBuildTimer < m_Level3PowerPoint)
	{
		// Shoot Level 2 Projectile
		m_PowerLevel = 2;

		// Spawn an instance of the Blueprint class using the GetWorld()->SpawnActor function
		AActor* SpawnActor = GetWorld()->SpawnActor(m_Projectile2, &SpawnTransform);

		SpawnProjectileBP = m_Projectile2;
	}
	else if (m_CurrentBuildTimer >= m_Level3PowerPoint)
	{
		// Shoot Level 3 Projectile
		m_PowerLevel = 3;

		// Spawn an instance of the Blueprint class using the GetWorld()->SpawnActor function
		AActor* SpawnActor = GetWorld()->SpawnActor(m_Projectile3, &SpawnTransform);

		SpawnProjectileBP = m_Projectile3;
	}
}


