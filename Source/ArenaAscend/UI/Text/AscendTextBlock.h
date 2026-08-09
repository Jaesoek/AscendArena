#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "AscendTextBlock.generated.h"

UCLASS(meta = (DisplayName = "Ascend Text"))
class ARENAASCEND_API UAscendTextBlock : public UTextBlock
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Ascend|Text")
	void SetHangulSubstitutionEnabled(bool bEnabled);

	UFUNCTION(BlueprintPure, Category = "Ascend|Text")
	bool IsHangulSubstitutionEnabled() const { return bEnableHangulSubstitution; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ascend|Text", BlueprintGetter = IsHangulSubstitutionEnabled, BlueprintSetter = SetHangulSubstitutionEnabled, meta = (DisplayName = "Enable Hangul Substitution"))
	bool bEnableHangulSubstitution = false;

	virtual TAttribute<FText> GetDisplayText() override;

private:
	FText GetSubstitutedText();
};
