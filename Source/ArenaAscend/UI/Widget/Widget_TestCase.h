#pragma once

#include <CoreMinimal.h>
#include <Blueprint/UserWidget.h>
#include "Widget_TestCase.generated.h"

class UImage;
class UCanvasPanel;

UCLASS()
class ARENAASCEND_API UWidget_TestCase : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> C_CP_Test;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> C_Img_This;
};
