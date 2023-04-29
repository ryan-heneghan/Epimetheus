#pragma once

#include "CoreMinimal.h"
#include "MatchStateHandler.h"
#include "New_ThirdPersonCharacter_Tut.h"
#include "GameFramework/PlayerController.h"
#include "GEP_PlayerController_Tut.generated.h"

class UInputMappingContext;

UCLASS(Abstract)
class EPIMETHEUS_API AGEP_PlayerController_Tut : public APlayerController, public IMatchStateHandler
{
	GENERATED_BODY()

public:
	AGEP_PlayerController_Tut();

	UFUNCTION(BlueprintNativeEvent)
	void Init();

	virtual void Handle_MatchStarted_Implementation() override;
	virtual void Handle_MatchEnded_Implementation() override;

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<APawn> PawnToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	
};
