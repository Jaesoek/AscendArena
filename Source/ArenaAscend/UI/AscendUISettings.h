#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "AscendUISettings.generated.h"

class AAscendHUD;
class UAscendPopupBase;
class UAscendSceneBase;

USTRUCT()
struct FAscendHUDRegistryEntry
{
	GENERATED_BODY()

	UPROPERTY(Config, EditDefaultsOnly, Category = "HUD")
	TSoftClassPtr<AAscendHUD> HUDClass;

	UPROPERTY(Config, EditDefaultsOnly, Category = "HUD")
	FName DefaultSceneId;
};

UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "Ascend UI"))
class ARENAASCEND_API UAscendUISettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UAscendUISettings();

	static const UAscendUISettings* Get() { return GetDefault<UAscendUISettings>(); }

	TSubclassOf<AAscendHUD> GetHUDClass(FName HUDId) const;
	FName GetDefaultSceneId(FName HUDId) const;
	TSubclassOf<UAscendSceneBase> GetSceneClass(FName SceneId) const;
	TSubclassOf<UAscendPopupBase> GetPopupClass(FName PopupId) const;

protected:
	UPROPERTY(Config, EditDefaultsOnly, Category = "HUD")
	TMap<FName, FAscendHUDRegistryEntry> HUDRegistry;

	UPROPERTY(Config, EditDefaultsOnly, Category = "Scene")
	TMap<FName, TSoftClassPtr<UAscendSceneBase>> SceneRegistry;

	UPROPERTY(Config, EditDefaultsOnly, Category = "Popup")
	TMap<FName, TSoftClassPtr<UAscendPopupBase>> PopupRegistry;
};
