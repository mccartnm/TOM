// Alpha Tango Games  For Fun and Profit! 2020

#pragma once

#include "CoreMinimal.h"
#include "MountableBase.h"
#include "MountableEngine.generated.h"

/**
 * 
 */
UCLASS()
class TOM_API AMountableEngine : public AMountableBase
{
	GENERATED_BODY()
	
protected:
    EMountType MountType() const override { return EMountType::Engine; }
};
