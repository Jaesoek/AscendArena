#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AscendGameMode.generated.h"

UCLASS()
class ARENAASCEND_API AAscendGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAscendGameMode();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Ascend|UI")
	FName DefaultHUDId = TEXT("HUD.InGame");

	/** 각 페이즈의 지속 시간(초)입니다. 배열 순서가 페이즈 순서입니다. */
	UPROPERTY(EditDefaultsOnly, Category = "Ascend|Phase", meta = (ClampMin = "0.01"))
	TArray<float> PhaseDurations = { 60.0f, 60.0f, 60.0f };

	/** 페이즈가 시작될 때 서버에서 호출됩니다. 실제 몬스터 스폰 로직은 이후 이 이벤트에 연결합니다. */
	UFUNCTION(BlueprintNativeEvent, Category = "Ascend|Phase")
	void SpawnMonstersForPhase(int32 PhaseNumber);
	virtual void SpawnMonstersForPhase_Implementation(int32 PhaseNumber);

	/** 설정된 마지막 페이즈가 끝난 뒤 서버에서 호출됩니다. */
	UFUNCTION(BlueprintImplementableEvent, Category = "Ascend|Phase")
	void OnAllPhasesCompleted();

private:
	FTimerHandle PhaseTimerHandle;
	int32 ActivePhaseIndex = INDEX_NONE;

	void StartPhase(int32 PhaseIndex);
	void AdvancePhase();
};
