#include "AscendTextBlock.h"

#include "AscendHangulSubstitution.h"

void UAscendTextBlock::SetHangulSubstitutionEnabled(bool bEnabled)
{
	if (bEnableHangulSubstitution == bEnabled)
	{
		return;
	}

	bEnableHangulSubstitution = bEnabled;
	SynchronizeProperties();
}

TAttribute<FText> UAscendTextBlock::GetDisplayText()
{
	if (!bEnableHangulSubstitution)
	{
		return Super::GetDisplayText();
	}

	return TAttribute<FText>::Create(
		TAttribute<FText>::FGetter::CreateUObject(this, &UAscendTextBlock::GetSubstitutedText));
}

FText UAscendTextBlock::GetSubstitutedText()
{
	const FText SourceText = Super::GetDisplayText().Get();
	return FText::FromString(FAscendHangulSubstitution::SubstituteWithLatin(SourceText.ToString()));
}
