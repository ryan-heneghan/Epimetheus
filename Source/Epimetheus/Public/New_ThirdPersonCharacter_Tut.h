// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "New_ThirdPersonCharacter_Tut.generated.h"

// Stops circular definitions??? makes sense... i think
class UCameraComponent;
class UInputMappingContext;
class UInputAction;

class AWeapon_Base;

UCLASS(Abstract)
class EPIMETHEUS_API ANew_ThirdPersonCharacter_Tut : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> WeaponAttachPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* PlayerMappingContext;	// Errors because rider isnt up to date with new input system

	// Need input action for each type of action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta=(AllowPrivateAccess = "true"))
	UInputAction* ShootAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta=(AllowPrivateAccess = "true"))
	UInputAction* CrouchAction;
	
public:
	// Sets default values for this character's properties
	ANew_ThirdPersonCharacter_Tut();

protected:
	// Called when the game starts or when spawned

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AWeapon_Base> DefaultWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<AActor> FireableReference;
	
	virtual void BeginPlay() override;

	// Callback function for inout
	void Move(const FInputActionValue& Value);
	void Jump();
	void Shoot();
	void Crouch();
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
