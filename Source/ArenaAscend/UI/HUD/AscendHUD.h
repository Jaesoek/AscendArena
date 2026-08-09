#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AscendHUD.generated.h"

class UAscendPopupBase;
class UAscendSceneBase;

UCLASS()
class ARENAASCEND_API AAscendHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintCallable, Category = "Ascend|HUD")
	UAscendSceneBase* ChangeSceneById(FName SceneId);

	UFUNCTION(BlueprintCallable, Category = "Ascend|HUD")
	UAscendPopupBase* PushPopupById(FName PopupId);

	UFUNCTION(BlueprintCallable, Category = "Ascend|HUD")
	void PopPopup();

	UFUNCTION(BlueprintCallable, Category = "Ascend|HUD")
	void ClearPopups();

	UFUNCTION(BlueprintPure, Category = "Ascend|HUD")
	UAscendSceneBase* GetCurrentScene() const { return CurrentScene; }

	UFUNCTION(BlueprintPure, Category = "Ascend|HUD")
	int32 GetPopupCount() const { return PopupStack.Num(); }

protected:
	virtual void InitializeHUD();

	UFUNCTION(BlueprintImplementableEvent, Category = "Ascend|HUD")
	void BP_OnHUDInitialized();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ascend|HUD")
	FName HUDId;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ascend|HUD")
	FName DefaultSceneId;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "Ascend|HUD")
	TObjectPtr<UAscendSceneBase> CurrentScene;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "Ascend|HUD")
	TArray<TObjectPtr<UAscendPopupBase>> PopupStack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ascend|HUD")
	int32 SceneZOrder = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ascend|HUD")
	int32 PopupBaseZOrder = 100;

private:
	UAscendSceneBase* ChangeSceneInternal(TSubclassOf<UAscendSceneBase> InSceneClass);
	UAscendPopupBase* PushPopupInternal(TSubclassOf<UAscendPopupBase> InPopupClass);
};
