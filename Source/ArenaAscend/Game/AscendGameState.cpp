#include "AscendGameState.h"

#include "Net/UnrealNetwork.h"

float AAscendGameState::GetPhaseRemainingSeconds() const
{
	return FMath::Max(0.0f, PhaseEndServerTime - GetServerWorldTimeSeconds());
}

void AAscendGameState::SetPhaseState(const int32 NewPhase, const float NewPhaseEndServerTime)
{
	check(HasAuthority());

	const int32 PreviousPhase = CurrentPhase;
	CurrentPhase = NewPhase;
	PhaseEndServerTime = NewPhaseEndServerTime;
	ForceNetUpdate();
	NotifyPhaseChanged(PreviousPhase);
}

void AAscendGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAscendGameState, CurrentPhase);
	DOREPLIFETIME(AAscendGameState, PhaseEndServerTime);
}

void AAscendGameState::OnRep_PhaseState()
{
	NotifyPhaseChanged(LastNotifiedPhase);
}

void AAscendGameState::NotifyPhaseChanged(const int32 PreviousPhase)
{
	if (PreviousPhase == CurrentPhase)
	{
		return;
	}

	LastNotifiedPhase = CurrentPhase;
	OnPhaseChanged.Broadcast(PreviousPhase, CurrentPhase);
}
