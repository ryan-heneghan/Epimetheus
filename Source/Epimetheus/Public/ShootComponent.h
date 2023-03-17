// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShootComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FShootComponent, bool, startBuilding, float, currentBuildTime);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EPIMETHEUS_API UShootComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UShootComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable, Category = "Components")
	FShootComponent onComponentBuild;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Shooting")
	bool m_CanStartBuilding;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Shooting")
	float m_CurrentBuildTimer;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Shooting")
	float m_MaxBuildTime;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Shooting")
	float m_Level1PowerPoint;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Shooting")
	float m_Level2PowerPoint;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Shooting")
	float m_Level3PowerPoint;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Shooting")
	int m_PowerLevel;
	
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
	void BuildProjectile();

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
	void ShootProjectile();

	// Different Projectile Levels
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Shooting")
	AActor* m_SpawnLocation;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Shooting")
	UClass* m_Projectile1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Shooting")
	UClass* m_Projectile2;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Shooting")
	UClass* m_Projectile3;
};
