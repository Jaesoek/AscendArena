#include "AscendGameMode.h"

#include "ArenaAscend/Game/AscendGameState.h"
#include "ArenaAscend/Player/AscendPlayerController.h"
#include "ArenaAscend/UI/AscendUISettings.h"
#include "ArenaAscend/UI/HUD/AscendHUDInGame.h"

#include "UObject/ConstructorHelpers.h"

AAscendGameMode::AAscendGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	PlayerControllerClass = AAscendPlayerController::StaticClass();

	if (const UAscendUISettings* UISettings = UAscendUISettings::Get())
	{
		HUDClass = UISettings->GetHUDClass(DefaultHUDId);
	}

	if (HUDClass == nullptr)
	{
		HUDClass = AAscendHUDInGame::StaticClass();
	}

	GameStateClass = AAscendGameState::StaticClass();
}

void AAscendGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (PhaseDurations.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("No phase durations were configured. Phase progression will not start."));
		return;
	}

	StartPhase(0);
}

void AAscendGameMode::SpawnMonstersForPhase_Implementation(const int32 PhaseNumber)
{
	// Intentionally empty. Phase-specific monster spawning will be added here later.
}

void AAscendGameMode::StartPhase(const int32 PhaseIndex)
{
	check(HasAuthority());
	check(PhaseDurations.IsValidIndex(PhaseIndex));

	ActivePhaseIndex = PhaseIndex;
	const float PhaseDuration = FMath::Max(0.01f, PhaseDurations[ActivePhaseIndex]);
	const float PhaseEndTime = GetWorld()->GetTimeSeconds() + PhaseDuration;

	if (AAscendGameState* AscendGameState = GetGameState<AAscendGameState>())
	{
		AscendGameState->SetPhaseState(ActivePhaseIndex + 1, PhaseEndTime);
	}

	SpawnMonstersForPhase(ActivePhaseIndex + 1);
	GetWorldTimerManager().SetTimer(PhaseTimerHandle, this, &ThisClass::AdvancePhase, PhaseDuration, false);
}

void AAscendGameMode::AdvancePhase()
{
	const int32 NextPhaseIndex = ActivePhaseIndex + 1;
	if (PhaseDurations.IsValidIndex(NextPhaseIndex))
	{
		StartPhase(NextPhaseIndex);
		return;
	}

	GetWorldTimerManager().ClearTimer(PhaseTimerHandle);
	OnAllPhasesCompleted();
}
