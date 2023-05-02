// Fill out your copyright notice in the Description page of Project Settings.

#include "Particles/ParticleSystemComponent.h"
#include "EnemyHealthComponent.h"

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

	EnemySelf->GetOwner();
	
	CurrentHealth = MaxHealth;
	CurrentHealthPercent = CurrentHealth / MaxHealth;
}

void UEnemyHealthComponent::DamageTaken(AActor* damagedActor, float damageTaken, const UDamageType* damageType, AController* instigator, AActor* damager)
{
	// Take damage
	CurrentHealth -= damageTaken;

	UpdateEnemyHealthBar();

	// Particle effects
	if (CurrentHealthPercent <= .25)
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
		
		// Hides actors, no garbage collection
		damagedActor->Destroy();
	}
}

void UEnemyHealthComponent::UpdateEnemyHealthBar()
{
	// Updates enemy health bar
	CurrentHealthPercent = CurrentHealth / MaxHealth;
}


