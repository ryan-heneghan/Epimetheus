// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnemyComponentDead, AController*, causer);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EPIMETHEUS_API UEnemyHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyHealthComponent();

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FEnemyComponentDead OnEnemyDead;

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
	void UpdateEnemyHealthBar();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite)
	AActor* EnemySelf;
	
	// Health Variables
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
	float MaxHealth;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Health")
	float CurrentHealth;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Health")
	float CurrentHealthPercent;

	// Death
	// Particles
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Death")
	UParticleSystemComponent* LowHealthEffect;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Death")
	UParticleSystemComponent* ExplosionEffect;

	UFUNCTION()
	void DamageTaken(AActor* damagedActor, float damageTaken, const UDamageType* damageType, AController* instigator, AActor* damager);

	// Visual Effects
};
