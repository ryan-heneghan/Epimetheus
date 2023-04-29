// Fill out your copyright notice in the Description page of Project Settings.


#include "Basic_Projectile.h"


// Sets default values
ABasic_Projectile::ABasic_Projectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABasic_Projectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasic_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

