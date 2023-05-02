// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "WeaponSelectorComponent.h"

UWeaponSelectorComponent::UWeaponSelectorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UWeaponSelectorComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(DefaultAction, ETriggerEvent::Triggered, this, &UWeaponSelectorComponent::BasicSwitch);

		EnhancedInputComponent->BindAction(BounceAction, ETriggerEvent::Triggered, this, &UWeaponSelectorComponent::BounceSwitch);
		
		EnhancedInputComponent->BindAction(WaveAction, ETriggerEvent::Triggered, this, &UWeaponSelectorComponent::WaveSwitch);

	}
}


void UWeaponSelectorComponent::BeginPlay()
{
	Super::BeginPlay();
	
	SelectedWeapon = EWeaponList::Basic;
}

void UWeaponSelectorComponent::BasicSwitch()
{
	SelectedWeapon = EWeaponList::Basic;
}

void UWeaponSelectorComponent::BounceSwitch()
{
	SelectedWeapon = EWeaponList::Bounce;
}

void UWeaponSelectorComponent::WaveSwitch()
{
	SelectedWeapon = EWeaponList::Wave;
}


