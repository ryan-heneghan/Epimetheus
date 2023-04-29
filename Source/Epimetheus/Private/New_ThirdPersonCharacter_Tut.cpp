#include "New_ThirdPersonCharacter_Tut.h"

#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

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
