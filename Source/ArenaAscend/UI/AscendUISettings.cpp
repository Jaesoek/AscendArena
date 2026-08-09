#include "AscendUISettings.h"

#include "ArenaAscend/UI/HUD/AscendHUD.h"
#include "ArenaAscend/UI/Screen/AscendPopupBase.h"
#include "ArenaAscend/UI/Screen/AscendSceneBase.h"

UAscendUISettings::UAscendUISettings()
{
	CategoryName = TEXT("Project");
	SectionName = TEXT("Ascend UI");
}

TSubclassOf<AAscendHUD> UAscendUISettings::GetHUDClass(FName HUDId) const
{
	const FAscendHUDRegistryEntry* Entry = HUDRegistry.Find(HUDId);
	return (Entry == nullptr || Entry->HUDClass.IsNull()) ? nullptr : Entry->HUDClass.LoadSynchronous();
}

FName UAscendUISettings::GetDefaultSceneId(FName HUDId) const
{
	const FAscendHUDRegistryEntry* Entry = HUDRegistry.Find(HUDId);
	return Entry == nullptr ? NAME_None : Entry->DefaultSceneId;
}

TSubclassOf<UAscendSceneBase> UAscendUISettings::GetSceneClass(FName SceneId) const
{
	const TSoftClassPtr<UAscendSceneBase>* SceneClass = SceneRegistry.Find(SceneId);
	return (SceneClass == nullptr || SceneClass->IsNull()) ? nullptr : SceneClass->LoadSynchronous();
}

TSubclassOf<UAscendPopupBase> UAscendUISettings::GetPopupClass(FName PopupId) const
{
	const TSoftClassPtr<UAscendPopupBase>* PopupClass = PopupRegistry.Find(PopupId);
	return (PopupClass == nullptr || PopupClass->IsNull()) ? nullptr : PopupClass->LoadSynchronous();
}
