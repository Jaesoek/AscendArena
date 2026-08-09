#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AscendPlayerController.generated.h"

UCLASS()
class ARENAASCEND_API AAscendPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void PlayerTick(float DeltaTime) override;

private:
	/** Smoothness of the character's horizontal rotation toward the mouse cursor. */
	UPROPERTY(EditDefaultsOnly, Category = "Aiming", meta = (ClampMin = "0.0"))
	float CursorRotationInterpSpeed = 15.0f;

	/** Collision channel used to find the world position beneath the mouse cursor. */
	UPROPERTY(EditDefaultsOnly, Category = "Aiming")
	TEnumAsByte<ECollisionChannel> CursorTraceChannel = ECC_Visibility;

	void UpdateCursorFacing(float DeltaTime);
};
