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
	if (m_CurrentBuildTimer < m_Level2PowerPoint)
	{
		// Shoot Level 1 Projectile
		m_PowerLevel = 1;

		FVector spawnLoc = (m_SpawnLocation->GetActorLocation());
		FRotator spawnRot = (m_SpawnLocation->GetActorRotation());
		FActorSpawnParameters spawnInfo;
		
		m_Projectile1 = GetWorld()->SpawnActor<UClass>(spawnLoc, spawnRot, spawnInfo);
		
	}
	else if (m_CurrentBuildTimer >= m_Level2PowerPoint && m_CurrentBuildTimer < m_Level3PowerPoint)
	{
		// Shoot Level 2 Projectile
		m_PowerLevel = 2;

		FVector spawnLoc(0.f, 0.f, 0.f);
		FRotator spawnRot(0.f, 0.f, 0.f);;
		FActorSpawnParameters spawnInfo;
		
		m_Projectile2 = GetWorld()->SpawnActor<UClass>(spawnLoc, spawnRot, spawnInfo);
	}
	else if (m_CurrentBuildTimer >= m_Level3PowerPoint)
	{
		// Shoot Level 1 Projectile
		m_PowerLevel = 3;

		FVector spawnLoc = (m_SpawnLocation->GetActorLocation());
		FRotator spawnRot = (m_SpawnLocation->GetActorRotation());
		FActorSpawnParameters spawnInfo;
		
		m_Projectile3 = GetWorld()->SpawnActor<UClass>(spawnLoc, spawnRot, spawnInfo);
	}

	m_CanStartBuilding = true;
	m_CurrentBuildTimer = 0.f;
}


