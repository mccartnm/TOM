// Alpha Tango Games  For Fun and Profit! 2020

#pragma once

#include "CoreMinimal.h"
#include "MountableBase.h"
#include "MountableEngine.generated.h"

/**
 * An engine produces thrust. The sum total of all engines
 * on a vessel divded by the mass of the hull and mounts determines
 * the speed at which it can move
 */
UCLASS()
class TOM_API AMountableEngine : public AMountableBase
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Properties)
    float Force = 100.0;

protected:
    EMountType MountType() const override { return EMountType::Engine; }
};
