#include "New_ThirdPersonCharacter_Tut.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Fireable.h"
#include "Weapon_Base.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(LogCharacterTut, Display, All);

ANew_ThirdPersonCharacter_Tut::ANew_ThirdPersonCharacter_Tut()
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.f);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetCapsuleComponent());
	Camera->SetRelativeLocation(FVector(-50.f, 0.f, 100.f));
	Camera->bUsePawnControlRotation = false;

	WeaponAttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponAttachPoint"));
	//WeaponAttachPoint->SetupAttachment(Player);
}

void ANew_ThirdPersonCharacter_Tut::BeginPlay()
{
	Super::BeginPlay();

	// Setup weapon in world
	if(DefaultWeapon)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = this;
		TObjectPtr<AActor> SpawnedWeapon = GetWorld()->SpawnActor(DefaultWeapon, &WeaponAttachPoint->GetComponentTransform(), SpawnParams);
		SpawnedWeapon->AttachToComponent(WeaponAttachPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);
		// Saves reference if implements interface
		if (UKismetSystemLibrary::DoesImplementInterface(SpawnedWeapon, UFireable::StaticClass()))
		{
			FireableReference = SpawnedWeapon;
		}
	}

	// Setup mapping context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Turns on our specific controls if true
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
		}
	}
}

void ANew_ThirdPersonCharacter_Tut::Move(const FInputActionValue& Value)
{
	float MovementValue = Value.Get<float>();

	if (Controller != nullptr)
	{
		AddMovementInput(GetActorRightVector(), MovementValue);
	}
}

void ANew_ThirdPersonCharacter_Tut::Jump()
{
	
}

void ANew_ThirdPersonCharacter_Tut::Shoot()
{
	if (FireableReference)
	{
		IFireable::Execute_Fire(FireableReference);
	}
}

void ANew_ThirdPersonCharacter_Tut::Crouch()
{
}

void ANew_ThirdPersonCharacter_Tut::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ANew_ThirdPersonCharacter_Tut::Move);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &ANew_ThirdPersonCharacter_Tut::Shoot);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &ANew_ThirdPersonCharacter_Tut::Crouch);
	}
}
