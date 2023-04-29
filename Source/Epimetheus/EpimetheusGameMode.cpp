// Copyright Epic Games, Inc. All Rights Reserved.

#include "EpimetheusGameMode.h"
#include "EpimetheusCharacter.h"
#include "GEP_PlayerController_Tut.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AEpimetheusGameMode::AEpimetheusGameMode() : Super()
{
	CountdownTimer = 3;
}

AActor* AEpimetheusGameMode::FindPlayerStart_Implementation(AController* Player, const FString& IncomingName)
{
	if (PlayerStarts.Num() == 0)
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);
		
	}

	if (PlayerStarts.Num() > 0)
	{
		return PlayerStarts[0];
	}

	return nullptr;
}

void AEpimetheusGameMode::PostLogin(APlayerController* NewPlayer)
{
	PlayerControllers.AddUnique(NewPlayer);
	if(AGEP_PlayerController_Tut* CastedPC = Cast<AGEP_PlayerController_Tut>(NewPlayer))
	{
		// TODO: bind to any relevant events
		CastedPC->Init();
	}
	
	Super::PostLogin(NewPlayer);
}

void AEpimetheusGameMode::Logout(AController* Exiting)
{
	PlayerControllers.Remove(Exiting);
	
	Super::Logout(Exiting);
}

void AEpimetheusGameMode::DecreaseCountdown()
{
	CountdownTimer--;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("%D"), CountdownTimer));

	// Start match if timer hit zero
	if (CountdownTimer <= 0)
	{
		StartMatch();
	}
	else // Count down again if not finished
	{
		GetWorld()->GetTimerManager().SetTimer(TimerDecreaseCountdown, this, &AEpimetheusGameMode::DecreaseCountdown, 1.f, false);
	}
}

void AEpimetheusGameMode::BeginPlay()
{
	Super::BeginPlay();

	// TODO: Add game rule stuff here
}

void AEpimetheusGameMode::HandleMatchIsWaitingToStart()
{
	GetWorld()->GetTimerManager().SetTimer(TimerDecreaseCountdown, this, &AEpimetheusGameMode::DecreaseCountdown, 1.f, false);
	
	Super::HandleMatchIsWaitingToStart();
}

void AEpimetheusGameMode::HandleMatchHasStarted()
{
	for (AController* Controller : PlayerControllers)
	{
		if (UKismetSystemLibrary::DoesImplementInterface(Controller, UMatchStateHandler::StaticClass()))
		{
			IMatchStateHandler::Execute_Handle_MatchStarted(Controller);
		}
	}
	
	Super::HandleMatchHasStarted();
}

void AEpimetheusGameMode::HandleMatchHasEnded()
{
	for (AController* Controller : PlayerControllers)
	{
		if (UKismetSystemLibrary::DoesImplementInterface(Controller, UMatchStateHandler::StaticClass()))
		{
			IMatchStateHandler::Execute_Handle_MatchEnded(Controller);
		}
	}
	
	Super::HandleMatchHasEnded();
}

void AEpimetheusGameMode::OnMatchStateSet()
{
	FString Output;
	if(MatchState == MatchState::WaitingToStart)
	{
		Output = "Waiting to start";
	}
	else if (MatchState == MatchState::InProgress)
	{
		Output = "In Progress";
	}
	else if (MatchState == MatchState::WaitingPostMatch)
	{
		Output = "Waiting post match";
	}
	else if (MatchState == MatchState::LeavingMap)
	{
		Output = "Leaving Map";
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Turquoise, FString::Printf(TEXT("State Changed to: %s"), *Output));
	
	Super::OnMatchStateSet();
}

bool AEpimetheusGameMode::ReadyToStartMatch_Implementation()
{
	return false;
}

bool AEpimetheusGameMode::ReadyToEndMatch_Implementation()
{
	return false;
}
