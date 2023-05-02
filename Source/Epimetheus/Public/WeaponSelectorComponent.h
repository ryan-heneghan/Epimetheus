// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Components/ActorComponent.h"
#include "WeaponSelectorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EPIMETHEUS_API UWeaponSelectorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponSelectorComponent();

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);
	
	virtual void BeginPlay() override;

	// Input voids
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
	void BasicSwitch();
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
	void BounceSwitch();
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
	void WaveSwitch();
	
	
public:	

	// Enum for holding different weapons
	enum class EWeaponList : int {
		Basic	= 0	UMETA(DisplayName = "Basic"),
		Bounce	= 1	UMETA(DisplayName = "Bounce"),
		Wave	= 2	UMETA(DisplayName = "Wave"),
		None	= 3
	};

	EWeaponList SelectedWeapon;

	// How to get input again?
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* DefaultAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* BounceAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* WaveAction;
};
