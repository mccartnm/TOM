// Alpha Tango Games  For Fun and Profit! 2020


#include "HardpointBase.h"

// Sets default values for this component's properties
UHardpointBase::UHardpointBase()
{
	MountActorChildComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("Mount"));
	MountActorChildComponent->SetupAttachment(this);

	PrimaryComponentTick.bCanEverTick = false; // For the time being
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


bool UHardpointBase::CanMountClass(TSubclassOf<AMountableBase> Mount) const
{
	AMountableBase* Instance = Mount.GetDefaultObject();

	int32 MountType = static_cast<int32>(Instance->GetMountType());
	if (MountType & (SupportedMountTypes / 2)) // FIXME BP Bitmask is doubling?
	{
		return true;
	}
	return false;
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


bool UHardpointBase::SetMount(TSubclassOf<AMountableBase> Mount)
{
	ClearMount();
	if (!Mount || !CanMountClass(Mount))
	{
		SetBlankMount();
		return false;
	}
	MountActorChildComponent->SetChildActorClass(Mount);
	MountActorChildComponent->CreateChildActor();
	return true;
}


void UHardpointBase::ClearMount()
{
	MountActorChildComponent->DestroyChildActor();
}


void UHardpointBase::BeginPlay()
{
	Super::BeginPlay();
}


void UHardpointBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
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
