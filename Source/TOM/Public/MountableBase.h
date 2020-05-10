// Alpha Tango Games  For Fun and Profit! 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MountableBase.generated.h"

/*
 * Mount Type is the root type all mountable objects can obtain
 */
UENUM(BlueprintType, Meta = (Bitflags))
enum class EMountType : uint8
{
	Invalid = 0x00 UMETA(ToolTip = "Invalid Mount Type - Must be First"),

	Engine = 0x01 UMETA(ToolTip = "Engine - Produces thrust"),
	Weapon = 0x02 UMETA(ToolTip = "Weapon - Can deal damage on some kind"),
	Core   = 0x04 UMETA(ToolTip = "Core - Some mannger of power or power up"),
};


UCLASS()
class TOM_API AMountableBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMountableBase();

	UFUNCTION(BlueprintCallable, Category=Mount)
	EMountType GetMountType() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Return the type of mountable this is
	virtual EMountType MountType() const { return EMountType::Invalid; }

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
