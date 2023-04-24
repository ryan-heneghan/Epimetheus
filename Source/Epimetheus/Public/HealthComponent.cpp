// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	m_MaxHealth = 100.f;
	IsInvincible = false;
	InvincibilityTimer = 3.f;
	CurrentInvincibleTIme = 0.f;

	m_MaxShieldh = 100.0f;
	m_CurrentShield = 50.0f;
	CurrentLives = 3;

	SpawnLocationOffset = FVector3d(60.0f, 0.0f, 40.0f);
	Player = GetOwner();
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	
	m_CurrentHealth = m_MaxHealth;

	Player = GetOwner();
	
	UpdateBars();
}

void UHealthComponent::DamageTaken(AActor* damagedActor, float damageTaken, const UDamageType* damageType, AController* instigator, AActor* damager)
{
	if (!damageType->bCausedByWorld && IsInvincible)
		return;
	
	// Takes away damage amount by shield amount, but locks it at 0
	float LeftOverDamage = FMath::Max(damageTaken - m_CurrentShield, 0.f);
	m_CurrentShield = FMath::Max(m_CurrentShield - damageTaken, 0.f);

	if (LeftOverDamage > 0.f)
	{
		m_CurrentHealth = FMath::Max(m_CurrentHealth - LeftOverDamage, 0.f);
	}

	if (m_CurrentHealth <= 0.f)
	{
		onComponentDead.Broadcast(instigator);
	}

	UpdateBars();

	// Sets timer for invincibility
	if (!damageType->bCausedByWorld)
	{
		IsInvincible = true;
		CurrentInvincibleTIme = InvincibilityTimer;
		InvincibleEffect->Activate(true);	
	}
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Players invincibility timer
	// Starts after getting hit
	if (!IsInvincible)
	{
		return;
	}
	
	if (CurrentInvincibleTIme > 0.f)
	{
		InvincibleEffect->SetWorldLocation(Player->GetActorLocation() + SpawnLocationOffset);
		CurrentInvincibleTIme -= DeltaTime;
	}
	else
	{
		IsInvincible = false;
		InvincibleEffect->Deactivate();
	}
}

void UHealthComponent::UpdateBars()
{
	// Change percentage
	CurrentShieldPercent = m_CurrentShield / m_MaxShieldh;
	CurrentHealthPercent = m_CurrentHealth / m_MaxHealth;
}

void UHealthComponent::AddHealthOrShield(float AddedHealth, float AddedShield)
{
	m_CurrentHealth += AddedHealth;
	if (m_CurrentHealth > m_MaxHealth)
	{
		m_CurrentHealth = m_MaxHealth;
	}

	m_CurrentShield += AddedShield;
	if (m_CurrentShield > m_MaxShieldh)
	{
		m_CurrentShield = m_MaxShieldh;
	}

	UpdateBars();
}

void UHealthComponent::TakeLife()
{
	CurrentLives--;
}

