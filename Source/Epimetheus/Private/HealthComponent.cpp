// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	m_MaxHealth = 100.f;
	m_CanRegenHealth = true;
	m_HealthRecoverRate = 10.f;
	m_HealthRecoverDelay = 2.f;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	
	m_CurrentHealth = m_MaxHealth;
}

void UHealthComponent::DamageTaken(AActor* damagedActor, float damageTaken, const UDamageType* damageType, AController* instigator, AActor* damager)
{
	float leftOverDamage = FMath::Max(damageTaken - m_CurrentHealth, 0.f);
	m_CurrentHealth = FMath::Max(m_CurrentHealth - damageTaken, 0.f);
	m_HealthRegenDelayTimer = m_HealthRecoverDelay;

	if (leftOverDamage > 0.f)
	{
		m_CurrentHealth = FMath::Max(m_CurrentHealth - leftOverDamage, 0.f);
	}

	if (m_CurrentHealth <= 0.f)
	{
		onComponentDead.Broadcast(instigator);
	}
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