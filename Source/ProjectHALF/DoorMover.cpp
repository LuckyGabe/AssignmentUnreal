// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorMover.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"
// Sets default values for this component's properties
UDoorMover::UDoorMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
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

	//for checking if the player or an enemy is near
// For moving the door
	FVector CurrentPosition = GetOwner()->GetActorLocation();
	FVector TargetPosition = OriginalLocation + MoveOffSet;

	if(GetAllowedActor() != nullptr)
	{
		bShouldMove = true;

	}

	else 
	{
		bShouldMove = false;

	}

	
	float MoveSpeed = FVector::Dist(OriginalLocation, TargetPosition) / MoveTime;

	FVector DefaultLocation = FMath::VInterpConstantTo(CurrentPosition, OriginalLocation, DeltaTime, MoveSpeed);
	FVector NewLocation = FMath::VInterpConstantTo(CurrentPosition, TargetPosition, DeltaTime, MoveSpeed);

	if (bShouldMove)
	{
		GetOwner()->SetActorLocation(NewLocation);
		UE_LOG(LogTemp, Warning, TEXT("PlayerDetected"));
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
	UClass* seekClass = NULL;

		UKismetSystemLibrary::BoxOverlapActors(GetWorld(), GetOwner()->GetActorLocation() - FVector(0, 200.0f, 200.0f), BoxCheckSize, TraceObjectTypes, NULL, IgnoreActors, OverlappingActors);
		DrawDebugBox(GetWorld(), GetOwner()->GetActorLocation() - FVector(0, 200.0f, 200.0f), BoxCheckSize, FColor::Red, false, 1);
		for (AActor* actor : OverlappingActors)
		{
			if (actor->ActorHasTag("Player") || actor->ActorHasTag("Enemy"))
			{
				
				return actor;
			}

		}

		return nullptr;

}