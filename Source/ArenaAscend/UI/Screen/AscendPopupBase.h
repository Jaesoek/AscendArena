#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AscendPopupBase.generated.h"

class AAscendHUD;
class UAscendSceneBase;

UCLASS(Abstract, Blueprintable)
class ARENAASCEND_API UAscendPopupBase : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Ascend|Popup")
	void InitializePopup(AAscendHUD* InOwningHUD, UAscendSceneBase* InOwningScene);

	UFUNCTION(BlueprintCallable, Category = "Ascend|Popup")
	virtual void OnAddedToStack();

	UFUNCTION(BlueprintCallable, Category = "Ascend|Popup")
	virtual void OnRemovedFromStack();

	UFUNCTION(BlueprintPure, Category = "Ascend|Popup")
	AAscendHUD* GetAscendHUD() const { return OwningHUD.Get(); }

	UFUNCTION(BlueprintPure, Category = "Ascend|Popup")
	UAscendSceneBase* GetOwningScene() const { return OwningScene.Get(); }

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Ascend|Popup")
	void BP_OnPopupInitialized();

	UFUNCTION(BlueprintImplementableEvent, Category = "Ascend|Popup")
	void BP_OnPopupPushed();

	UFUNCTION(BlueprintImplementableEvent, Category = "Ascend|Popup")
	void BP_OnPopupPopped();

	UPROPERTY(BlueprintReadOnly, Category = "Ascend|Popup")
	TObjectPtr<AAscendHUD> OwningHUD;

	UPROPERTY(BlueprintReadOnly, Category = "Ascend|Popup")
	TObjectPtr<UAscendSceneBase> OwningScene;
};
