#include "GEP_PlayerController_Tut.h"

#include "EnhancedInputSubsystems.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

AGEP_PlayerController_Tut::AGEP_PlayerController_Tut() : Super()
{
}

void AGEP_PlayerController_Tut::Init_Implementation()
{
	// Setup player mapping context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// Turns on our specific controls if true
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// Makes ure player controller is on its own
	if (GetPawn() != nullptr)
	{
		GetPawn()->Destroy();
	}
}

void AGEP_PlayerController_Tut::Handle_MatchStarted_Implementation()
{
	UWorld* const World = GetWorld();

	// Return player start for respawn
	AActor* TempStart = UGameplayStatics::GetGameMode(World)->FindPlayerStart(this);
	FVector const spawnLocation = TempStart != nullptr ? TempStart->GetActorLocation() : FVector::ZeroVector;
	FRotator const SpawnRotation = TempStart != nullptr ? TempStart->GetActorRotation() : FRotator::ZeroRotator;
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	// Spawns pawn into world
	APawn* TempPawn = World->SpawnActor<APawn>(PawnToSpawn, spawnLocation, SpawnRotation, SpawnParams);

	// Casts temp pawn to variable and stores it, runs if successful
	if (ANew_ThirdPersonCharacter_Tut* CastedPawn = Cast<ANew_ThirdPersonCharacter_Tut>(TempPawn))
	{
		// TODO: Bind to any relevant events
		CastedPawn->Init();
	}
}

void AGEP_PlayerController_Tut::Handle_MatchEnded_Implementation()
{
	// Change input mode to UI only
	//SetInputMode(FInputModeUIOnly());
}
