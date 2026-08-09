#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AscendAttributeSet.generated.h"

UCLASS()
class ARENAASCEND_API UAscendAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	int32 KillPoint;
};
