// Alpha Tango Games  For Fun and Profit! 2020


#include "HardpointBase.h"

// Sets default values for this component's properties
UHardpointBase::UHardpointBase()
{
	MountActorChildComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("Mount"));
	MountActorChildComponent->SetupAttachment(this);

	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


void UHardpointBase::MountChanged_Implementation()
{
	// We need to have a class at least and possibly a 
	if ((*MountedClass) /*&& (!GetMount() || (GetMount()->GetClass() != MountedClass))*/)
	{
		SetMount(MountedClass);
	}
	else
	{
		ClearMount();
		SetBlankMount();
	}
}


AMountableBase* UHardpointBase::GetMount() const
{
	if (!MountActorChildComponent)
		return nullptr;

	// Might return a nullptr but we'll check for that
	AActor* actor = MountActorChildComponent->GetChildActor();
	if (!actor)
		return nullptr;

	if (AMountableBase* p = Cast<AMountableBase>(actor))
	{
		// Double check this isn't a blank mount
		if (p->GetMountType() == EMountType::Invalid)
			return nullptr;
		return p;
	}



	return nullptr;
}


bool UHardpointBase::SetMount(TSubclassOf<AMountableBase> mount)
{
	ClearMount();
	if (!mount)
	{
		SetBlankMount();
		return false;
	}

	// Verify this mount and handle the mount type
	int32 mountType = static_cast<int32>(mount.GetDefaultObject()->GetMountType());
	if (mountType & (SupportedMountTypes / 2)) // FIXME BP Bitmask is doubling?
	{
		MountActorChildComponent->SetChildActorClass(mount);
		MountActorChildComponent->CreateChildActor();
		return true;
	}

	// Cannot set that mount type. Should be caught earlier
	SetBlankMount();
	return false;
}


void UHardpointBase::ClearMount()
{
	MountActorChildComponent->DestroyChildActor();
}


// Called when the game starts
void UHardpointBase::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHardpointBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


#if WITH_EDITOR
void UHardpointBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	// For in-editor use. We want to detect changes made to our
	FString String = PropertyChangedEvent.GetPropertyName().ToString();
	if (String == FString("SupportedMountTypes") || String == FString("MountedClass"))
	{
		//UE_LOG(LogTemp, Warning, TEXT("TEST"));
		MountChanged();
	}

	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif


void UHardpointBase::SetBlankMount()
{
	MountActorChildComponent->SetChildActorClass(AMountableBase::StaticClass());
	MountActorChildComponent->CreateChildActor();
}
