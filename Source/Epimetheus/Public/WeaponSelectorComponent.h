// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "WeaponSelectorComponent.generated.h"


// Enum for holding different weapons
UENUM(BlueprintType)
enum class EWeaponList : uint8 {
	Basic	UMETA(DisplayName = "Basic"),
	Bounce	UMETA(DisplayName = "Bounce"),
	Wave	UMETA(DisplayName = "Wave"),
	None
};

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<EWeaponList> SelectedWeapon;

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
