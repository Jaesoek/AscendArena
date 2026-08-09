#include "AscendPlayerController.h"

#include "Engine/EngineTypes.h"
#include "GameFramework/Pawn.h"

void AAscendPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController())
	{
		bShowMouseCursor = true;
	}
}

void AAscendPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (IsLocalController())
	{
		UpdateCursorFacing(DeltaTime);
	}
}

void AAscendPlayerController::UpdateCursorFacing(float DeltaTime)
{
	FHitResult CursorHit;
	const ETraceTypeQuery TraceType = UEngineTypes::ConvertToTraceType(CursorTraceChannel);
	if (!GetHitResultUnderCursorByChannel(TraceType, false, CursorHit))
	{
		return;
	}

	APawn* ControlledPawn = GetPawn();
	if (!IsValid(ControlledPawn))
	{
		return;
	}

	FVector DirectionToCursor = CursorHit.ImpactPoint - ControlledPawn->GetActorLocation();
	DirectionToCursor.Z = 0.0f;
	if (DirectionToCursor.IsNearlyZero())
	{
		return;
	}

	const FRotator TargetRotation(0.0f, DirectionToCursor.Rotation().Yaw, 0.0f);
	const FRotator SmoothedRotation = FMath::RInterpTo(
		ControlledPawn->GetActorRotation(),
		TargetRotation,
		DeltaTime,
		CursorRotationInterpSpeed);

	ControlledPawn->SetActorRotation(SmoothedRotation);
}
