#include "AscendHUD.h"

#include "ArenaAscend/UI/AscendUISettings.h"
#include "ArenaAscend/UI/Screen/AscendPopupBase.h"
#include "ArenaAscend/UI/Screen/AscendSceneBase.h"

#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"

void AAscendHUD::BeginPlay()
{
	Super::BeginPlay();

	InitializeHUD();
}

void AAscendHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	ClearPopups();

	if (IsValid(CurrentScene))
	{
		CurrentScene->OnRemovedFromStack();
		CurrentScene->RemoveFromParent();
		CurrentScene = nullptr;
	}

	Super::EndPlay(EndPlayReason);
}

UAscendSceneBase* AAscendHUD::ChangeSceneInternal(TSubclassOf<UAscendSceneBase> InSceneClass)
{
	if (!IsValid(PlayerOwner) || !IsValid(InSceneClass))
	{
		return nullptr;
	}

	if (IsValid(CurrentScene))
	{
		CurrentScene->OnRemovedFromStack();
		CurrentScene->RemoveFromParent();
		CurrentScene = nullptr;
	}

	CurrentScene = CreateWidget<UAscendSceneBase>(PlayerOwner, InSceneClass);
	if (!IsValid(CurrentScene))
	{
		return nullptr;
	}

	CurrentScene->InitializeScene(this);
	CurrentScene->AddToViewport(SceneZOrder);
	CurrentScene->OnAddedToStack();

	ClearPopups();
	return CurrentScene;
}

UAscendSceneBase* AAscendHUD::ChangeSceneById(FName SceneId)
{
	if (SceneId.IsNone())
	{
		return nullptr;
	}

	const UAscendUISettings* UISettings = UAscendUISettings::Get();
	return UISettings == nullptr ? nullptr : ChangeSceneInternal(UISettings->GetSceneClass(SceneId));
}

UAscendPopupBase* AAscendHUD::PushPopupInternal(TSubclassOf<UAscendPopupBase> InPopupClass)
{
	if (!IsValid(PlayerOwner) || !IsValid(InPopupClass))
	{
		return nullptr;
	}

	UAscendPopupBase* NewPopup = CreateWidget<UAscendPopupBase>(PlayerOwner, InPopupClass);
	if (!IsValid(NewPopup))
	{
		return nullptr;
	}

	NewPopup->InitializePopup(this, CurrentScene);
	NewPopup->AddToViewport(PopupBaseZOrder + PopupStack.Num());
	NewPopup->OnAddedToStack();
	PopupStack.Add(NewPopup);

	return NewPopup;
}

UAscendPopupBase* AAscendHUD::PushPopupById(FName PopupId)
{
	if (PopupId.IsNone())
	{
		return nullptr;
	}

	const UAscendUISettings* UISettings = UAscendUISettings::Get();
	return UISettings == nullptr ? nullptr : PushPopupInternal(UISettings->GetPopupClass(PopupId));
}

void AAscendHUD::PopPopup()
{
	if (PopupStack.IsEmpty())
	{
		return;
	}

	UAscendPopupBase* Popup = PopupStack.Pop();
	if (!IsValid(Popup))
	{
		return;
	}

	Popup->OnRemovedFromStack();
	Popup->RemoveFromParent();
}

void AAscendHUD::ClearPopups()
{
	while (!PopupStack.IsEmpty())
	{
		PopPopup();
	}
}

void AAscendHUD::InitializeHUD()
{
	if (DefaultSceneId.IsNone())
	{
		if (const UAscendUISettings* UISettings = UAscendUISettings::Get())
		{
			DefaultSceneId = UISettings->GetDefaultSceneId(HUDId);
		}
	}

	if (!DefaultSceneId.IsNone())
	{
		ChangeSceneById(DefaultSceneId);
	}

	BP_OnHUDInitialized();
}
