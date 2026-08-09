#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "AscendGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAscendPhaseChanged, int32, PreviousPhase, int32, NewPhase);

UCLASS()
class ARENAASCEND_API AAscendGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	/** 1부터 시작하는 현재 페이즈 번호입니다. 0은 아직 페이즈가 시작되지 않았음을 뜻합니다. */
	UPROPERTY(ReplicatedUsing = OnRep_PhaseState, BlueprintReadOnly, Category = "Ascend|Phase")
	int32 CurrentPhase = 0;

	/** 현재 페이즈가 끝나는 서버 월드 시간입니다. 클라이언트는 GetServerWorldTimeSeconds와 비교해 남은 시간을 계산합니다. */
	UPROPERTY(ReplicatedUsing = OnRep_PhaseState, BlueprintReadOnly, Category = "Ascend|Phase")
	float PhaseEndServerTime = 0.0f;

	UPROPERTY(BlueprintAssignable, Category = "Ascend|Phase")
	FAscendPhaseChanged OnPhaseChanged;

	UFUNCTION(BlueprintPure, Category = "Ascend|Phase")
	float GetPhaseRemainingSeconds() const;

	void SetPhaseState(int32 NewPhase, float NewPhaseEndServerTime);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UFUNCTION()
	void OnRep_PhaseState();

private:
	int32 LastNotifiedPhase = 0;

	void NotifyPhaseChanged(int32 PreviousPhase);
};
