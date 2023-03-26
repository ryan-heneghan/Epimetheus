// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	m_MaxHealth = 100.f;
	m_CanRegenHealth = false;
	m_HealthRecoverRate = 10.f;
	m_HealthRecoverDelay = 2.f;

	m_MaxShieldh = 100.0f;
	m_CurrentShield = 50.0f;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	
	m_CurrentHealth = m_MaxHealth;
	
	UpdateBars();
}

void UHealthComponent::DamageTaken(AActor* damagedActor, float damageTaken, const UDamageType* damageType, AController* instigator, AActor* damager)
{
	// Takes away damage amount by shield amount, but locks it at 0
	float LeftOverDamage = FMath::Max(damageTaken - m_CurrentShield, 0.f);
	m_CurrentShield = FMath::Max(m_CurrentShield - damageTaken, 0.f);

	if (LeftOverDamage > 0.f)
	{
		m_CurrentHealth = FMath::Max(m_CurrentHealth - LeftOverDamage, 0.f);
		m_HealthRegenDelayTimer = m_HealthRecoverDelay;
	}

	if (m_CurrentHealth <= 0.f)
	{
		onComponentDead.Broadcast(instigator);
	}

	UpdateBars();
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_CurrentHealth == m_MaxHealth || m_CanRegenHealth == false)
	{
		return;
	}
	
	if (m_HealthRegenDelayTimer > 0.f)
	{
		m_HealthRegenDelayTimer -= DeltaTime;
	}
	else
	{
		m_CurrentHealth = FMath::Min(m_MaxHealth, m_CurrentHealth + (m_HealthRecoverRate * DeltaTime));
	}
}

void UHealthComponent::UpdateBars()
{
	// Change percentage
	CurrentShieldPercent = m_CurrentShield / m_MaxShieldh;
	CurrentHealthPercent = m_CurrentHealth / m_MaxHealth;
}
