#include "ShootComponent.h"
#include "WeaponSelectorComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values for this component's properties
UShootComponent::UShootComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

	m_PowerLevel = 1;
	m_CurrentBuildTimer = 0.f;
	m_CanStartBuilding = false;
	
	m_Level2PowerPoint = 0.5f;
	m_Level3PowerPoint = 1.5f;

	MaxBulletPerSecond = 2;
	MaxShootCooldownTimer = 1;
	
	SpawnLocationOffset = FVector3d(60.0f, 0.0f, 40.0f);
	
	Player = GetOwner();
}


// Called when the game starts
void UShootComponent::BeginPlay()
{
	Super::BeginPlay();

	m_CurrentBuildTimer = 0.f;
	CurrentShootCooldownTimer = 0.f;
	Player = GetOwner();
}


// Called every frame
void UShootComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Ammo timer thing
	// Start cooldown timer when shoot
	if (CurrentBulletAmount > 0)
	{
		if (CurrentShootCooldownTimer <= 0)
		{
			CurrentBulletAmount = 0;
			CurrentShootCooldownTimer = MaxShootCooldownTimer;
		}
		else
		{
			CurrentShootCooldownTimer -= DeltaTime;
		}
	}

	// Decide if the player has enough ammo
	if (CurrentBulletAmount > MaxBulletPerSecond)
	{
		OutOfAmmo = true;
	}
	else
	{
		OutOfAmmo = false;
	}

	// Building power timer
	if (!m_CanStartBuilding)
	{
		return;
	}
	
	m_CurrentBuildTimer += DeltaTime;
	ChargingEffect->SetWorldLocation(Player->GetActorLocation() + SpawnLocationOffset);
	
	if (m_CurrentBuildTimer >= m_MaxBuildTime)
	{
		ShootProjectile();
	}
}

void UShootComponent::BuildProjectile()
{
	// Dont let player build if used max bullets per second
	if (OutOfAmmo)
		return;
	
	m_CurrentBuildTimer = 0.f;
	m_CanStartBuilding = true;
	ChargingEffect->Activate(true);
}


void UShootComponent::ShootProjectile()
{
	// Doesnt shoot if the player wasn't building
	//For when players lets go of mouse button after already shooting from having full charge
	if (!m_CanStartBuilding)
		return;

	// Dont let player shoot if used max bullets per second
	if (OutOfAmmo)
		return;
	
	// Stop building power
	m_CanStartBuilding = false;
	ChargingEffect->Deactivate();

	// Get the world location of the arrow component
	//FVector const SpawnLocation = Player->GetActorLocation() + SpawnLocationOffset;
	FVector const SpawnLocation = ProjSpawnComp->GetComponentLocation();

	// Set the desired rotation for the spawned actor
	FRotator const SpawnRotation = Player->GetActorRotation();

	// Create a new FTransform object using the spawn location and rotation
	SpawnTransform = FTransform(SpawnRotation, SpawnLocation);
	
	if (m_CurrentBuildTimer < m_Level2PowerPoint)
	{
		// Shoot Level 1 Projectile
		m_PowerLevel = 1;

		// Spawn an instance of the Blueprint class using the GetWorld()->SpawnActor function
		SpawnActor = GetWorld()->SpawnActor(m_Projectile1, &SpawnTransform);

		SpawnProjectileBP = m_Projectile1;
	}
	else if (m_CurrentBuildTimer >= m_Level2PowerPoint && m_CurrentBuildTimer < m_Level3PowerPoint)
	{
		// Shoot Level 2 Projectile
		m_PowerLevel = 2;

		// Spawn an instance of the Blueprint class using the GetWorld()->SpawnActor function
		SpawnActor = GetWorld()->SpawnActor(m_Projectile2, &SpawnTransform);

		SpawnProjectileBP = m_Projectile2;
	}
	else if (m_CurrentBuildTimer >= m_Level3PowerPoint)
	{
		// Shoot Level 3 Projectile
		m_PowerLevel = 3;

		// Spawn an instance of the Blueprint class using the GetWorld()->SpawnActor function
		SpawnActor = GetWorld()->SpawnActor(m_Projectile3, &SpawnTransform);

		SpawnProjectileBP = m_Projectile3;
	}

	// Increase bullet account for ammo
	CurrentBulletAmount++;
}


