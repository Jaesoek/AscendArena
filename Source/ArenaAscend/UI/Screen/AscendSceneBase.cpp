#include "AscendSceneBase.h"

#include "ArenaAscend/Player/AscendPlayerController.h"
#include "ArenaAscend/UI/HUD/AscendHUD.h"

void UAscendSceneBase::InitializeScene(AAscendHUD* InOwningHUD)
{
	OwningHUD = InOwningHUD;
	BP_OnSceneInitialized();
}

void UAscendSceneBase::OnAddedToStack()
{
	BP_OnScenePushed();
}

void UAscendSceneBase::OnRemovedFromStack()
{
	BP_OnScenePopped();
}

AAscendPlayerController* UAscendSceneBase::GetAscendPlayerController() const
{
	return IsValid(OwningHUD.Get()) ? Cast<AAscendPlayerController>(OwningHUD->GetOwningPlayerController()) : nullptr;
}
