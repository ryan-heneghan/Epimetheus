// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponSelectorComponent.h"
#include "GameFramework/Character.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "HeadMountedDisplayTypes.h"

UWeaponSelectorComponent::UWeaponSelectorComponent()
{

}

void UWeaponSelectorComponent::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
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
}

void UWeaponSelectorComponent::BasicSwitch()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Default") ));
	SelectedWeapon = EWeaponList::Basic;
}

void UWeaponSelectorComponent::BounceSwitch()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Bounce") ));
	SelectedWeapon = EWeaponList::Bounce;
}

void UWeaponSelectorComponent::WaveSwitch()
{
	SelectedWeapon = EWeaponList::Wave;
}


