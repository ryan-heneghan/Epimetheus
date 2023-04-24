// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Windows.Media.Audio.h>

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "TurretAIComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EPIMETHEUS_API UTurretAIComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTurretAIComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Functions for checking
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
	void CheckDistance();

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
	void LookAtPlayer();

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
	void TurretShoot();

	// Actor Variables
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Actor")
	AActor* Player;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Actor")
	AActor* Turret;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Actor")
	UStaticMeshComponent* TurretHead;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Actor")
	FVector TurretPosition;

	// Time variables
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Time")
	float CheckTime;
	float CurrentCheckTime;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Time")
	float RotationSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Time")
	float FireRate;
	float CurrentFireTime;

	float CurrentDeltaTime;
	
	// Distance Variables
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Distance")
	FVector DistanceVector;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Distance")
	float DistanceFromPlayer;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Distance")
	float DistanceForClose;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Distance")
	bool IsPlayerClose;

	// Shooting Variables
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Shooting")
	FVector FirePositionOffset;
	FTransform SpawnTransform;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Shooting")
	UClass* TurretProjectile;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Shooting")
	AActor* SpawnBulletActor;
	
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
