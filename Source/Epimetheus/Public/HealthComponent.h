// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FComponentDeadSignature, AController*, causer);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EPIMETHEUS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();
	
	// Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable, Category = "Components")
	FComponentDeadSignature onComponentDead;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Health")
	float m_CurrentHealth;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
	float m_MaxHealth;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Health")
	bool m_CanRegenHealth;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Health")
	float m_HealthRegenDelayTimer;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
	float m_HealthRecoverRate;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
	float m_HealthRecoverDelay;

	UFUNCTION()
	void DamageTaken(AActor* damagedActor, float damageTaken, const UDamageType* damageType, AController* instigator, AActor* damager);
};