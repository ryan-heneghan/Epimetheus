// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Basic_Projectile.generated.h"

UCLASS()
class EPIMETHEUS_API ABasic_Projectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABasic_Projectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
