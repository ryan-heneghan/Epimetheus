// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootComponent.h"

// Sets default values for this component's properties
UShootComponent::UShootComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

	m_PowerLevel = 1;
	m_CurrentBuildTimer = 0.f;
	m_CanStartBuilding = false;
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
}

void UShootComponent::BuildProjectile()
{
	m_CanStartBuilding = true;
}


void UShootComponent::ShootProjectile()
{
	if (m_CurrentBuildTimer < m_Level2PowerPoint)
	{
		// Shoot Level 1 Projectile
		m_PowerLevel = 1;
	}
	else if (m_CurrentBuildTimer >= m_Level2PowerPoint && m_CurrentBuildTimer < m_Level3PowerPoint)
	{
		// Shoot Level 2 Projectile
		m_PowerLevel = 2;
	}
	else if (m_CurrentBuildTimer >= m_Level3PowerPoint)
	{
		// Shoot Level 1 Projectile
		m_PowerLevel = 3;
	}
}


