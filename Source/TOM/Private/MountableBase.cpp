// Alpha Tango Games  For Fun and Profit! 2020


#include "MountableBase.h"

// Sets default values
AMountableBase::AMountableBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* component = CreateDefaultSubobject<USceneComponent>(TEXT("MountRoot"));
	RootComponent = component;
}

EMountType AMountableBase::GetMountType() const
{
	return MountType();
}

// Called when the game starts or when spawned
void AMountableBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMountableBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

