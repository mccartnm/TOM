// Alpha Tango Games  For Fun and Profit! 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Components/ChildActorComponent.h"
#include "MountableBase.h"
#include "HardpointBase.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class TOM_API UHardpointBase : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHardpointBase();

	UFUNCTION(BlueprintNativeEvent, Category="Mount Selected")
	void MountChanged();
	void MountChanged_Implementation();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Mount, Meta = (Bitmask, BitmaskEnum = "EMountType"))
	int32 SupportedMountTypes;

	// The class of the active mount. Mainly used for the editor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Mount)
	TSubclassOf<AMountableBase> MountedClass;

	UFUNCTION(BlueprintCallable, Category=Mount)
	AMountableBase *GetMount() const;

	UFUNCTION(BlueprintCallable, Category=Mount)
	bool SetMount(TSubclassOf<AMountableBase> mount);

	UFUNCTION(BlueprintCallable, Category=Mount)
	void ClearMount();

	// Child component that holds onto the mount.
	UPROPERTY(BlueprintReadOnly, Category=Mount)
	UChildActorComponent* MountActorChildComponent;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

#ifdef WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:

	void SetBlankMount();

};
