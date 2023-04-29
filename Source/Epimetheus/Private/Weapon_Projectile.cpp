#include "Weapon_Projectile.h"

#include "Components/ArrowComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponProj, Display, All);

bool AWeapon_Projectile::Fire_Implementation()
{
	UE_LOG(LogWeaponProj, Display, TEXT("Fire projectile weapon class!"));

	UWorld* const World = GetWorld();
	
	if (World == nullptr || Projectile == nullptr)
	{
		return false;
	}
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();	// Stops errors if gun is switched out
	SpawnParams.Instigator = GetInstigator();
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	World->SpawnActor(Projectile, &FirePoint->GetComponentTransform(), SpawnParams);

	return true;
}
