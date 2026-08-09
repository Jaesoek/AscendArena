#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AscendSceneBase.generated.h"

class AAscendHUD;
class AAscendPlayerController;

UCLASS(Abstract, Blueprintable)
class ARENAASCEND_API UAscendSceneBase : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Ascend|Scene")
	void InitializeScene(AAscendHUD* InOwningHUD);

	UFUNCTION(BlueprintCallable, Category = "Ascend|Scene")
	virtual void OnAddedToStack();

	UFUNCTION(BlueprintCallable, Category = "Ascend|Scene")
	virtual void OnRemovedFromStack();

	UFUNCTION(BlueprintPure, Category = "Ascend|Scene")
	AAscendHUD* GetAscendHUD() const { return OwningHUD.Get(); }

	UFUNCTION(BlueprintPure, Category = "Ascend|Scene")
	AAscendPlayerController* GetAscendPlayerController() const;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Ascend|Scene")
	void BP_OnSceneInitialized();

	UFUNCTION(BlueprintImplementableEvent, Category = "Ascend|Scene")
	void BP_OnScenePushed();

	UFUNCTION(BlueprintImplementableEvent, Category = "Ascend|Scene")
	void BP_OnScenePopped();

	UPROPERTY(BlueprintReadOnly, Category = "Ascend|Scene")
	TObjectPtr<AAscendHUD> OwningHUD;
};
