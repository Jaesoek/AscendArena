#include "AscendPopupBase.h"

void UAscendPopupBase::InitializePopup(AAscendHUD* InOwningHUD, UAscendSceneBase* InOwningScene)
{
	OwningHUD = InOwningHUD;
	OwningScene = InOwningScene;
	BP_OnPopupInitialized();
}

void UAscendPopupBase::OnAddedToStack()
{
	BP_OnPopupPushed();
}

void UAscendPopupBase::OnRemovedFromStack()
{
	BP_OnPopupPopped();
}
