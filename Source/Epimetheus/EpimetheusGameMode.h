// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "EpimetheusGameMode.generated.h"

UCLASS(minimalapi, Abstract)
class AEpimetheusGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AEpimetheusGameMode();

	virtual AActor* FindPlayerStart_Implementation(AController* Player, const FString& IncomingName) override;

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

protected:
	TArray<TObjectPtr<AActor>> PlayerStarts;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<AController>> PlayerControllers;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MatchManagement")
	int CountdownTimer;

	FTimerHandle TimerDecreaseCountdown;
	UFUNCTION()
	void DecreaseCountdown();

	virtual void BeginPlay() override;

	virtual void HandleMatchIsWaitingToStart() override;
	virtual void HandleMatchHasStarted() override;
	virtual void HandleMatchHasEnded() override;

	virtual void OnMatchStateSet() override;

	virtual bool ReadyToStartMatch_Implementation() override;
	virtual bool ReadyToEndMatch_Implementation() override;
};



