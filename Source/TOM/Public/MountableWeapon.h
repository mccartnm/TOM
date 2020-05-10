// Alpha Tango Games  For Fun and Profit! 2020

#pragma once

#include "CoreMinimal.h"
#include "MountableBase.h"
#include "MountableWeapon.generated.h"

/**
 * 
 */
UCLASS()
class TOM_API AMountableWeapon : public AMountableBase
{
	GENERATED_BODY()

protected:
    EMountType MountType() const override { return EMountType::Weapon; }
};
