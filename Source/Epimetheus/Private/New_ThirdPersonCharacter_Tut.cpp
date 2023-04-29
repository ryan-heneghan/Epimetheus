// Fill out your copyright notice in the Description page of Project Settings.


#include "New_ThirdPersonCharacter_Tut.h"

// Sets default values
ANew_ThirdPersonCharacter_Tut::ANew_ThirdPersonCharacter_Tut()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANew_ThirdPersonCharacter_Tut::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANew_ThirdPersonCharacter_Tut::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANew_ThirdPersonCharacter_Tut::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

