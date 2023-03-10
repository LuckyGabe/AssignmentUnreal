
#include "MyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
// Called when the game starts or when spawned
void AMyAIController::BeginPlay()
{
	Super::BeginPlay();
	if (AIBehaviorTree != nullptr)
	{
		RunBehaviorTree(AIBehaviorTree);
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());

	}
}
