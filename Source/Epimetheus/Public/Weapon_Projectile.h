// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon_Base.h"
#include "Epimetheus/Basic_Projectile.h"
#include "GameFramework/Actor.h"
#include "Weapon_Projectile.generated.h"

UCLASS(Abstract)
class EPIMETHEUS_API AWeapon_Projectile : public AWeapon_Base
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABasic_Projectile> Projectile;
	

public:
	virtual bool Fire_Implementation() override;
};
