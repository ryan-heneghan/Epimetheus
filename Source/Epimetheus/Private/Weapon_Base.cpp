#include "Weapon_Base.h"

#include "Components/ArrowComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponBase, Display, All);

AWeapon_Base::AWeapon_Base()
{
	// Basic setup
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	FirePoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Fire Point"));
	FirePoint->SetupAttachment(Mesh);
}

bool AWeapon_Base::Fire_Implementation()
{
	UE_LOG(LogWeaponBase, Display, TEXT("Fire the base weapon class"));
	return true;
}

void AWeapon_Base::BeginPlay()
{
	Super::BeginPlay();
}
