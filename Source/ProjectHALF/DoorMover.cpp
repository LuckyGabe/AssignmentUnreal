#include "DoorMover.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UDoorMover::UDoorMover()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UDoorMover::BeginPlay()
{
	Super::BeginPlay();

	OriginalLocation = GetOwner()->GetActorLocation();
}

// Called every frame
void UDoorMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// For moving the door
	FVector CurrentPosition = GetOwner()->GetActorLocation();
	FVector TargetPosition = OriginalLocation + MoveOffSet;

	time += DeltaTime;

	if (time > 0.3f) //timer to execute tracing every 0.3s for optimization
	{
		if (GetAllowedActor() != nullptr) // if tracing found a player
		{
			bShouldMove = true;
		}
		else if (!bLockedOpen)
		{
			bShouldMove = false;
		}

		time = 0.0f;
	}

	float MoveSpeed = FVector::Dist(OriginalLocation, TargetPosition) / MoveTime;
	FVector DefaultLocation = FMath::VInterpConstantTo(CurrentPosition, OriginalLocation, DeltaTime, MoveSpeed);
	FVector NewLocation = FMath::VInterpConstantTo(CurrentPosition, TargetPosition, DeltaTime, MoveSpeed);

	if (bShouldMove)
	{
		//Move actor 
		GetOwner()->SetActorLocation(NewLocation);
	}
	else
	{
		GetOwner()->SetActorLocation(DefaultLocation);
	}
}

AActor* UDoorMover::GetAllowedActor() const
{
	TArray<AActor*> OverlappingActors;
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;

	// Set what actors to seek out from it's collision channel
	TraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

	// Ignore any specific actors
	TArray<AActor*> IgnoreActors;
	UClass* seekClass = nullptr;
	FVector ActorCenter;
	FVector ActorSize;
	GetOwner()->GetActorBounds(true, ActorCenter, ActorSize); //get actor center

	//box overlap 
	UKismetSystemLibrary::BoxOverlapActors(GetWorld(), ActorCenter, BoxCheckSize, TraceObjectTypes, nullptr, IgnoreActors, OverlappingActors);

	for (AActor* actor : OverlappingActors)
	{
		if (actor->ActorHasTag("Player") || actor->ActorHasTag("Enemy"))
		{
			return actor;
		}
	}

	return nullptr;
}
