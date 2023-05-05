// Fill out your copyright notice in the Description page of Project Settings.

#include "Particles/ParticleSystemComponent.h"
#include "EnemyHealthComponent.h"

#include "Components/AudioComponent.h"

// Sets default values for this component's properties
UEnemyHealthComponent::UEnemyHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	
}


// Called when the game starts
void UEnemyHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UEnemyHealthComponent::DamageTaken);
	
	CurrentHealth = MaxHealth;
	CurrentHealthPercent = CurrentHealth / MaxHealth;

	EnemySelf = GetOwner();
}

void UEnemyHealthComponent::DamageTaken(AActor* damagedActor, float damageTaken, const UDamageType* damageType, AController* instigator, AActor* damager)
{
	// Take damage
	CurrentHealth -= damageTaken;

	// Updates enemy health bar
	CurrentHealthPercent = CurrentHealth / MaxHealth;

	// Particle effects
	if (CurrentHealthPercent <= .3)
	{
		if (LowHealthEffect != nullptr)
		{
			LowHealthEffect->SetWorldLocation(EnemySelf->GetActorLocation());
			LowHealthEffect->Activate(true);
		}
	}

	if (CurrentHealth <= 0)
	{
		if (ExplosionEffect != nullptr)
		{
			ExplosionEffect->SetWorldLocation(EnemySelf->GetActorLocation());
			ExplosionEffect->Activate(true);
		}

		if (DeathSound != nullptr)
		{
			DeathSound->Play(0);
		}
		// Hides actors, no garbage collection
		damagedActor->Destroy();
	}

	UpdateEnemyHealthBar();
}

void UEnemyHealthComponent::UpdateEnemyHealthBar()
{
	// Updates enemy health bar
	CurrentHealthPercent = CurrentHealth / MaxHealth;
}


