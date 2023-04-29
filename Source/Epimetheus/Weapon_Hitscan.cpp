#include "Weapon_Hitscan.h"

#include "Components/ArrowComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponHitscan, Display, All)

bool AWeapon_Hitscan::Fire_Implementation()
{
	UE_LOG(LogWeaponHitscan, Display, TEXT("Firing Hitscan weapon class"));

	UWorld* const World = GetWorld();
	if (World == nullptr)
	{
		return false;
	}

	FHitResult Hit(ForceInit);
	FVector Start = FirePoint->GetComponentLocation();
	FVector End = Start + (FirePoint->GetForwardVector() * 50);
	TArray<AActor*> ActorsToIgnore;

	// what
	if (UKismetSystemLibrary::LineTraceSingle(World, Start, End,
		UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel2), false,
		ActorsToIgnore, EDrawDebugTrace::ForDuration, Hit, true, FLinearColor::Red,
		FLinearColor::Green, 5.f))
	{
		UE_LOG(LogWeaponHitscan, Display, TEXT("Hit position: %s"), *Hit.ImpactPoint.ToString())
	}

	return true;
}
